#ifndef IRRIGATION_MANAGER_H
#define IRRIGATION_MANAGER_H

#include <Arduino.h> // Must include this to recognize pinMode, LOW, HIGH, etc.
#include "Constants.h"

/**
 * @class IrrigationManager
 * @brief Controls the water pump via an active-low relay module.
 */
class IrrigationManager {
private:
    bool isPumpRunning; // Keeps track of the current pump status

public:
    // Constructor
    IrrigationManager();

    // Initializes the relay pin and sets it to a safe state (OFF)
    void init();

    // Turns the water pump ON
    void turnOn();

    // Turns the water pump OFF
    void turnOff();

    // Returns true if the pump is currently running
    bool isOn();
};

#endif