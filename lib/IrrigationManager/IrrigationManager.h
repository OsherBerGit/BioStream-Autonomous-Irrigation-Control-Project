#pragma once
#include <Arduino.h>

/**
 * @class IrrigationManager
 * @brief Controls the water pump via a relay module using Dependency Injection.
 */
class IrrigationManager
{
private:
    uint8_t relayPin;      // Hardware pin connected to the relay
    uint8_t activeState;   // Logic level to turn the pump ON (e.g., LOW for Active-Low)
    uint8_t inactiveState; // Logic level to turn the pump OFF (e.g., HIGH)
    bool isPumpRunning;    // Keeps track of the current pump status

public:
    /**
     * @brief Constructor injecting the hardware configuration.
     * @param pin The digital pin connected to the relay.
     * @param isActiveLow Set to true if the relay triggers on LOW (default behavior).
     */
    IrrigationManager(uint8_t pin, bool isActiveLow = true);

    // Initializes the relay pin and sets it to a safe state (OFF)
    void init();

    // Turns the water pump ON
    void turnOn();

    // Turns the water pump OFF
    void turnOff();

    // Returns true if the pump is currently running
    bool isOn() const; // Marked as const since it doesn't modify the object
};