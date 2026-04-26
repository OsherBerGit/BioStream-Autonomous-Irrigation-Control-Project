#pragma once
#include <Arduino.h>

/**
 * @class InputManager
 * @brief Handles user input from the 4x4 matrix keypad.
 */
class InputManager {
public:
    // Initializes the keypad module
    void init();

    // Returns the character of the pressed key, or null ('\0') if no key is pressed
    char getPressedKey();
};