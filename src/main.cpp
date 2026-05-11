#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <RTClib.h>

// Custom Managers
#include "Constants.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "SensorManager.h"
#include "IrrigationManager.h"
#include "TimeManager.h"

// ============================================================================
// 1. Hardware Instantiation (Physical Layer)
// ============================================================================

// LCD Hardware
LiquidCrystal_I2C hardwareLcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

// Keypad Hardware mapping
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[KEYPAD_ROWS] = {KEYPAD_R1, KEYPAD_R2, KEYPAD_R3, KEYPAD_R4};
byte colPins[KEYPAD_COLS] = {KEYPAD_C1, KEYPAD_C2, KEYPAD_C3, KEYPAD_C4};
Keypad hardwareKeypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

// RTC Hardware
RTC_DS3231 hardwareRtc;

// ============================================================================
// 2. Dependency Injection: Manager Initialization (Abstraction Layer)
// ============================================================================

DisplayManager displayManager(hardwareLcd);
InputManager inputManager(hardwareKeypad);
SensorManager sensorManager(PIN_SOIL_MOISTURE, PIN_LDR, PIN_TEMP_SENSOR);
TimeManager clockManager(hardwareRtc);

// Inject relay pin and set Active-Low logic to true for safe initialization
IrrigationManager pumpManager(PIN_RELAY_PUMP, true);

// ============================================================================
// 3. State Machine & Global Variables
// ============================================================================

enum SystemState
{
    SYS_IDLE,
    SENSING,
    WATERING,
    CONFIG
};
SystemState currentState = SYS_IDLE;

unsigned long lastSensorReadTime = 0;
const unsigned long SENSOR_INTERVAL_MS = 1000; // 1-second interval for non-blocking read

unsigned long pumpStartTime = 0;
int moistureThreshold = DEFAULT_MOISTURE_THRESHOLD;
String inputBuffer = "";
bool systemLocked = false;
bool isAutoMode = true;

// ============================================================================
// Function Prototypes
// ============================================================================
void handleInput(char key);
void executeSensingState();
void executeWateringState();
void updateUI();

// ============================================================================
// Main Setup & Loop
// ============================================================================

void setup()
{
    Serial.begin(9600);
    Serial.println("BioStream-Autonomous Booting...");

    // Initialize all modular components
    displayManager.init();
    inputManager.init();
    sensorManager.init();
    pumpManager.init(); // Safely forces relay OFF immediately
    clockManager.init();

    displayManager.showWelcomeMessage();
}

void loop()
{
    // 1. Process Input continuously (Non-blocking)
    char key = inputManager.getPressedKey();
    if (key)
    {
        handleInput(key);
    }

    // 2. Execute State Machine Logic
    switch (currentState)
    {
    case IDLE:
        if (millis() - lastSensorReadTime >= SENSOR_INTERVAL_MS)
        {
            currentState = SENSING;
        }
        break;

    case SENSING:
        executeSensingState();
        break;

    case WATERING:
        executeWateringState();
        break;

    case CONFIG:
        // Handled entirely by UI updates and handleInput()
        break;
    }

    // 3. Update Visuals
    updateUI();
}

// ============================================================================
// Implementation of Logic Functions
// ============================================================================

void handleInput(char key)
{
    // Handle Global overrides
    if (key == 'A')
        isAutoMode = true;
    if (key == 'B')
    {
        isAutoMode = false;
        pumpManager.turnOff();
        currentState = SYS_IDLE;
    }

    // Safety Reset
    if (key == 'C' && systemLocked)
    {
        systemLocked = false;
        currentState = SYS_IDLE;
        Serial.println("Safety Lock Cleared via Keypad.");
    }

    // Menu Navigation
    if (key == '*')
    { // Enter Config Mode
        currentState = CONFIG;
        inputBuffer = "";
        displayManager.clear();
    }
    else if (key == '#')
    { // Confirm & Exit Config Mode
        if (currentState == CONFIG && inputBuffer.length() > 0)
        {
            moistureThreshold = inputBuffer.toInt();
            Serial.print("New Threshold set to: ");
            Serial.println(moistureThreshold);
        }
        currentState = SYS_IDLE;
        displayManager.clear();
    }
    else if (currentState == CONFIG)
    { // Numeric entry for config
        if (key >= '0' && key <= '9' && inputBuffer.length() < 2)
        {
            inputBuffer += key;
        }
    }
}

void executeSensingState()
{
    lastSensorReadTime = millis();

    // Only evaluate watering rules if in Auto mode and system is not locked
    if (isAutoMode && !systemLocked)
    {
        int moisture = sensorManager.readMoisturePercent();
        int light = sensorManager.readLightRaw();
        float temp = sensorManager.readTemperatureCelsius();

        int currentThreshold = moistureThreshold;

        // Environmental Rule 1: Heatwave Bonus
        if (temp > TEMP_MAX_HEATWAVE)
        {
            currentThreshold += HEATWAVE_BONUS_PCT;
        }

        // Evaluate conditions for watering
        bool needsWater = (moisture < currentThreshold);
        bool isTooBright = (light > LIGHT_THRESHOLD);
        bool isFreezing = (temp < TEMP_MIN_FREEZE);

        if (needsWater && !isTooBright && !isFreezing)
        {
            pumpManager.turnOn();
            pumpStartTime = millis();
            currentState = WATERING;
            Serial.println("Triggering Irrigation Phase...");
            return;
        }
    }

    currentState = SYS_IDLE;
}

void executeWateringState()
{
    // Safety Rule: Max run time timeout (Prevent flooding)
    if (millis() - pumpStartTime > MAX_PUMP_RUN_TIME)
    {
        pumpManager.turnOff();
        systemLocked = true;
        currentState = SYS_IDLE;
        Serial.println("CRITICAL: Max pump time reached. System locked!");
        return;
    }

    // Read moisture dynamically during watering
    if (millis() - lastSensorReadTime >= SENSOR_INTERVAL_MS)
    {
        lastSensorReadTime = millis();
        int currentMoisture = sensorManager.readMoisturePercent();

        // Stop watering once threshold is met
        if (currentMoisture >= moistureThreshold)
        {
            pumpManager.turnOff();
            currentState = SYS_IDLE;
            Serial.println("Irrigation Complete.");
        }
    }
}

void updateUI()
{
    if (currentState == CONFIG)
    {
        displayManager.updateTemperature(sensorManager.readTemperatureCelsius());
        displayManager.updateInputView(inputBuffer);
    }
    else
    {
        displayManager.updateTime(clockManager.getCurrentTimeString());
        displayManager.updateTemperature(sensorManager.readTemperatureCelsius());
        displayManager.updateMoisture(sensorManager.readMoisturePercent(), moistureThreshold);
        displayManager.updateLight(sensorManager.readLightRaw());
        displayManager.updateSystemStatus(isAutoMode, pumpManager.isOn(), systemLocked);
    }
}