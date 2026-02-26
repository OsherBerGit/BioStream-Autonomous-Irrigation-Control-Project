#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <Keypad.h>
#include "Constants.h"

class InputHandler {
private:
    Keypad keypad;

public:
    // Constructor initializes the keypad with constants
    InputHandler() : keypad(makeKeymap(KEYS), (byte*)ROW_PINS, (byte*)COL_PINS, ROWS, COLS) {}

    // Returns the pressed key or '\0' if none
    char getKey() {
        return keypad.getKey();
    }
};

#endif