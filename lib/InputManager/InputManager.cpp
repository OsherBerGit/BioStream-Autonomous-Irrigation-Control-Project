#include "InputManager.h"

// Initialization list to bind the external Keypad object to our reference
InputManager::InputManager(Keypad &keypadRef)
    : keypad(keypadRef) {}

void InputManager::init()
{
    // The Keypad library initializes itself upon creation,
    // but this method is kept for system architectural consistency.
}

char InputManager::getPressedKey()
{
    // Delegate the action to the injected Keypad object
    return keypad.getKey();
}