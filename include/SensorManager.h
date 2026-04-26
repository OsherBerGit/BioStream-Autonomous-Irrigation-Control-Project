#pragma once
#include <Arduino.h>
#include "Constants.h"

/**
 * @class SensorManager
 * @brief Manages data collection from analog sensors (Moisture, Light, Temperature).
 */
class SensorManager {
public:
    // Configure analog sensor pins as input pins
    void init();
    
    // Read moisture level as a percentage (0-100)
    int readMoisturePercent();
    
    // Read raw analog value (0-1023) from the LDR (light sensor)
    int readLightRaw();
    
    // Read the LM35 sensor and convert the voltage to degrees Celsius
    float readTemperatureCelsius();
};