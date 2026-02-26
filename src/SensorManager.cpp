#include "SensorManager.h"
#include <Arduino.h>

int SensorManager::readLight() {
    // Reads from A0. Higher value = More light.
    return analogRead(PIN_LDR);
}

int SensorManager::readMoisture() {
    // Returns the raw analog value (0 = Very Wet, 1023 = Very Dry)
    return analogRead(PIN_MOISTURE);
}

float SensorManager::readTemperature() {
    int rawBits = analogRead(PIN_LM35);

    // Convert ADC bits to voltage
    float voltage = (rawBits * ADC_VREF) / ADC_RES;
    
    // LM35 provides 10mV per degree Celsius (Voltage * 100)
    float celsius = voltage * 100.0;
    return celsius;
}