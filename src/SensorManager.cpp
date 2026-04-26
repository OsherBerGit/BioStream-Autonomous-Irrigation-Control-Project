#include "SensorManager.h"
#include <math.h>

const bool isWokwi = true; // Set to true for Wokwi simulation, false for real hardware

void SensorManager::init() {
    // Set all sensor pins to INPUT mode for analog reading
    pinMode(PIN_SOIL_MOISTURE, INPUT);
    pinMode(PIN_LDR, INPUT);
    pinMode(PIN_TEMP_SENSOR, INPUT);
}

int SensorManager::readMoisturePercent() {
    int rawValue = analogRead(PIN_SOIL_MOISTURE);
    
    // The Wokwi soil sensor (and many real ones) returns 0 for dry and 1023 for wet in some setups.
    // However, typical resistive sensors return 1023 for bone dry (high resistance) and ~0 for pure water.
    // We map it here. Assuming: 1023 = 0% (Dry), 0 = 100% (Wet).
    // Note: You might need to tweak these numbers (0, 1023) based on your specific physical sensor's dry/wet values.
    int percentage = map(rawValue, 1023, 0, 0, 100);
    
    // Constrain the value to be safely between 0 and 100
    return constrain(percentage, 0, 100);
}

int SensorManager::readLightRaw() {
    return analogRead(PIN_LDR);
}

float SensorManager::readTemperatureCelsius() {
    int analogValue = analogRead(PIN_TEMP_SENSOR);

    // If the sensor is disconnected or giving 0, return 0 to avoid crash
    if (analogValue == 0) return 0.0;

    // The LM35 formula is typically: Celsius = (Voltage in mV) / 10.
    // Since the ADC gives us a value from 0 to 1023 corresponding to 0 to 5V, we can convert it to voltage first, then to Celsius.
    float voltage = (float)analogValue * (5.0 / 1024.0); // Convert ADC value to voltage
    float celsius = voltage * 100.0; // Convert voltage to Celsius (10mV per degree for LM35)

    if (isWokwi) {
        // The Beta Coefficient (standard for Wokwi NTC is 3950)
        const float BETA = 3950;
        // The NTC Beta Formula
        celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
    }

    return celsius;
}