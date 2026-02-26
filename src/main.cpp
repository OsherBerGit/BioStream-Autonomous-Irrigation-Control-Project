#include <Arduino.h>
#include "SensorManager.h"
#include "IrrigationManager.h"
#include "DisplayManager.h"

// Instantiate modules
SensorManager sensors;
IrrigationManager pump;
DisplayManager display;

unsigned long lastTick = 0;
const unsigned long INTERVAL = 2000; // Check every 2 seconds

void setup() {
    Serial.begin(9600);

    // Initialize all modules
    pump.begin();
    display.begin();

    display.showWelcome(); // Method from our previous step
}

void loop() {
    unsigned long now = millis();

    // Main control loop (Non-blocking)
    if (now - lastTick >= INTERVAL) {
        lastTick = now;

        int soilMoisture = sensors.readMoisture();

        // Irrigation Logic: Control pump based on sensor data
        if (soilMoisture > MOISTURE_DRY_LIMIT) {
            pump.startPump();
            Serial.println("Action: Irrigation Started");
        } else {
            pump.stopPump();
            Serial.println("Action: Soil is hydrated");
        }

        // Update display with current status
        // display.updateScreen(soilMoisture, pump.isPumping());
    }
}