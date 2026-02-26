#ifndef IRRIGATION_MANAGER_H
#define IRRIGATION_MANAGER_H

#include "Constants.h"

class IrrigationManager {
private:
    bool _isPumping;

public:
    IrrigationManager() : _isPumping(false) {}

    // Initializes the relay pin and ensures pump is OFF
    void begin();

    // Direct control methods
    void startPump();
    void stopPump();

    // Returns current state
    bool isPumping() const { return _isPumping; }
};

#endif