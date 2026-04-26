#include "IrrigationManager.h"

// Constructor: Initializes the pump status variable to false
IrrigationManager::IrrigationManager() : isPumpRunning(false) {}

void IrrigationManager::init() {
    // Configure the relay pin as an output
    pinMode(PIN_RELAY_PUMP, OUTPUT);
    
    // Safety first: Ensure the pump is explicitly OFF when the system boots.
    turnOff();
}

void IrrigationManager::turnOn() {
    digitalWrite(PIN_RELAY_PUMP, PUMP_ON); // PUMP_ON is defined as LOW
    isPumpRunning = true;
}

void IrrigationManager::turnOff() {
    digitalWrite(PIN_RELAY_PUMP, PUMP_OFF); // PUMP_OFF is defined as HIGH
    isPumpRunning = false;
}

bool IrrigationManager::isOn() {
    return isPumpRunning;
}