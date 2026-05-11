#pragma once
#include <Arduino.h>
#include <Keypad.h>

/**
 * @class InputManager
 * @brief Handles user input from the matrix keypad using Dependency Injection.
 */
class InputManager
{
private:
    // DI: Store a reference to the external Keypad object
    Keypad &keypad;

public:
    // Constructor injecting the Keypad dependency
    InputManager(Keypad &keypadRef);

    // Initializes the keypad module
    void init();

    // Returns the character of the pressed key, or null ('\0') if no key is pressed
    char getPressedKey();
};