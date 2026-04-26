#include <Arduino.h>
#include "Constants.h"
#include "DisplayManager.h"
#include "SensorManager.h"
#include "IrrigationManager.h"
#include "TimeManager.h"
#include "InputManager.h"

// 1. Create instances of our managers (SOLID objects)
DisplayManager display(LCD_ADDRESS, LCD_COLS, LCD_ROWS);
SensorManager sensors;
IrrigationManager pump;
TimeManager clockManager;
InputManager keypad;

enum SystemState { MONITOR, SET_THRESHOLD };
SystemState currentState = MONITOR;
String inputBuffer = "";
int moistureThreshold = DEFAULT_MOISTURE_THRESHOLD;
bool isAutoMode = true;
unsigned long lastUpdate = 0;
unsigned long pumpStartTime = 0;
bool safetyLock = false;
bool lastPumpState = false;

void setup() {
    // Start Serial communication for debugging
    Serial.begin(9600);
    Serial.println("BioStream System Booting...");

    // 2. Initialize each module individually
    display.init();
    sensors.init();
    pump.init();
    clockManager.init();
    keypad.init();

    // Show welcome screen
    display.showWelcomeMessage();
}

void loop() {
    char key = keypad.getPressedKey();

    // 1. Keypad & State Handling
    if (key) {
        if (key == '#') { 
            // '#' acts as a Reset Safety button and Enter button
            if (currentState == SET_THRESHOLD && inputBuffer.length() > 0) {
                moistureThreshold = inputBuffer.toInt();
            }
            safetyLock = false;
            currentState = MONITOR;
            display.clear();
            Serial.println("System Reset / Safety Cleared");
        }
        else if (currentState == MONITOR && key == '*') {
            currentState = SET_THRESHOLD;
            inputBuffer = "";
            display.clear();
        } 
        else if (currentState == SET_THRESHOLD) {
            if (key >= '0' && key <= '9' && inputBuffer.length() < 2) {
                inputBuffer += key;
            }
        }
        else if (currentState == MONITOR) {
            // Manual mode overrides
            if (key == 'A') isAutoMode = true;
            if (key == 'B') isAutoMode = false;
        }
    }

    // 2. Monitoring & Logic
    if (currentState == MONITOR) {
        if (millis() - lastUpdate >= 500) {
            lastUpdate = millis();

            float t = sensors.readTemperatureCelsius();
            int m = sensors.readMoisturePercent();
            int light = sensors.readLightRaw();

            bool isTooBright = (light > LIGHT_THRESHOLD);
            bool isFreezing = (t < TEMP_MIN_FREEZE);
            bool isHeatwave = (t > TEMP_MAX_HEATWAVE);

            // Calculate the actual threshold needed right now
            int effectiveThreshold = moistureThreshold;
            if (isHeatwave) {
                effectiveThreshold += HEATWAVE_BONUS_PCT; // Require more water in heat
            }
            
            // --- Smart Irrigation Logic ---
            // Run IF: Not locked AND Auto mode AND Dry AND Not bright AND Not freezing
            if (!safetyLock && isAutoMode && m < effectiveThreshold && !isTooBright && !isFreezing) {
                if (!pump.isOn()) {
                    pump.turnOn();
                    pumpStartTime = millis();
                }
            } else {
                // If suddenly there is strong light, moisture increased, or manual override - turn off
                pump.turnOff(); 
            }

            // --- Safety Timeout Check ---
            if (pump.isOn()) {
                if (millis() - pumpStartTime > MAX_PUMP_RUN_TIME) {
                    pump.turnOff();
                    safetyLock = true;
                    Serial.println("SAFETY ERROR: Pump ran too long! System locked.");
                }
            }

            // --- 3. Display Updates ---
            display.updateTemperature(t);
            display.updateTime(clockManager.getCurrentTimeString());
            
            // Row 2 displays: Moisture, Light, and System Status
            display.updateMoisture(m, moistureThreshold);
            display.updateLight(light); 
            
            // Pass the safetyLock to show 'E' (Error) if the system is locked
            display.updateSystemStatus(isAutoMode, pump.isOn(), safetyLock);
        }
    } 
    else if (currentState == SET_THRESHOLD) {
        // Keep temperature visible while typing
        display.updateTemperature(sensors.readTemperatureCelsius()); 
        display.updateInputView(inputBuffer);
    }
}