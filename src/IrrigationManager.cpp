#include "IrrigationManager.h"
#include <Arduino.h>

void IrrigationManager::begin() {
    pinMode(PIN_RELAY, OUTPUT);
    stopPump(); // Safety: Ensure pump is OFF on system startup
}

void IrrigationManager::startPump() {
    digitalWrite(PIN_RELAY, PUMP_ON);
    _isPumping = true;
}

void IrrigationManager::stopPump() {
    digitalWrite(PIN_RELAY, PUMP_OFF);
    _isPumping = false;
}