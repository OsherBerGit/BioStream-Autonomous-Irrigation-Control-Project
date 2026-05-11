#include "IrrigationManager.h"

// Constructor: Initializes the hardware pin, logic states, and default pump status
IrrigationManager::IrrigationManager(uint8_t pin, bool isActiveLow)
    : relayPin(pin), isPumpRunning(false)
{

    // Determine the logic levels based on the relay hardware type
    if (isActiveLow)
    {
        activeState = LOW;
        inactiveState = HIGH;
    }
    else
    {
        activeState = HIGH;
        inactiveState = LOW;
    }
}

void IrrigationManager::init()
{
    // Configure the injected relay pin as an output
    pinMode(relayPin, OUTPUT);

    // SAFETY RULE: Ensure the pump is explicitly OFF when the system boots.
    // This protects the physically isolated 12V circuit from accidental flooding.
    turnOff();
}

void IrrigationManager::turnOn()
{
    digitalWrite(relayPin, activeState);
    isPumpRunning = true;
}

void IrrigationManager::turnOff()
{
    digitalWrite(relayPin, inactiveState);
    isPumpRunning = false;
}

bool IrrigationManager::isOn() const
{
    return isPumpRunning;
}