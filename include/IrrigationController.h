#ifndef IRRIGATION_MANAGER_H
#define IRRIGATION_MANAGER_H

#include "Constants.h"

class IrrigationManager {
public:
    void begin() {
        pinMode(PIN_PUMP, OUTPUT);
        stopPump(); // Safety: Ensure pump is OFF on boot
    }

    void startPump() {
        digitalWrite(PIN_PUMP, LOW); // Active Low: LOW turns relay ON
    }

    void stopPump() {
        digitalWrite(PIN_PUMP, HIGH); // Active Low: HIGH turns relay OFF
    }
};

#endif