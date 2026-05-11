#include "SensorManager.h"
#include <math.h>

// Constructor: Initializes the hardware pins for the sensors
SensorManager::SensorManager(uint8_t moisture, uint8_t light, uint8_t temp)
    : moisturePin(moisture), lightPin(light), tempPin(temp) {}

void SensorManager::init()
{
    // Set all injected sensor pins to INPUT mode for analog reading
    pinMode(moisturePin, INPUT);
    pinMode(lightPin, INPUT);
    pinMode(tempPin, INPUT);
}

int SensorManager::readMoisturePercent() const
{
    int rawValue = analogRead(moisturePin);

    // Typical resistive sensors return 1023 for bone dry (high resistance) and ~0 for pure water.
    // Map the raw value (0-1023) to a percentage (100%-0%).
    // Note: Calibration might be needed based on the specific physical sensor.
    int percentage = map(rawValue, 1023, 0, 0, 100);

    // Constrain the value to be safely between 0 and 100
    return constrain(percentage, 0, 100);
}

int SensorManager::readLightRaw() const
{
    return analogRead(lightPin);
}

float SensorManager::readTemperatureCelsius() const
{
    int analogValue = analogRead(tempPin);

    // If the sensor is disconnected or giving 0, return 0 to avoid crash/erroneous data
    if (analogValue == 0)
        return 0.0;

    // The LM35 formula is typically: Celsius = (Voltage in mV) / 10.
    // Convert ADC value (0-1023) to voltage (0-5.0V), then to Celsius.
    float voltage = (float)analogValue * (5.0 / 1024.0);
    float celsius = voltage * 100.0; // 10mV per degree for LM35

    return celsius;
}