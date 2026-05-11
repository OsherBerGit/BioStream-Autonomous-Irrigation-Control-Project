#pragma once
#include <Arduino.h>

/**
 * @class SensorManager
 * @brief Manages data collection from analog sensors using Dependency Injection.
 */
class SensorManager
{
private:
    // Hardware pins injected via constructor
    uint8_t moisturePin;
    uint8_t lightPin;
    uint8_t tempPin;

public:
    /**
     * @brief Constructor injecting hardware pin configurations.
     * @param moisture Analog pin for the soil moisture sensor.
     * @param light Analog pin for the LDR (light sensor).
     * @param temp Analog pin for the temperature sensor (e.g., LM35).
     */
    SensorManager(uint8_t moisture, uint8_t light, uint8_t temp);

    // Configure injected analog sensor pins as input
    void init();

    // Read moisture level as a percentage (0-100)
    int readMoisturePercent() const; // Marked const as it doesn't modify object state

    // Read raw analog value (0-1023) from the LDR (light sensor)
    int readLightRaw() const;

    // Read the LM35 sensor and convert the voltage to degrees Celsius
    float readTemperatureCelsius() const;
};