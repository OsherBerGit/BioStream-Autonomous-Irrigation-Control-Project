#include "InputManager.h"
#include <Keypad.h>
#include <Constants.h>

// 1. Define dimensions
const byte ROWS = KEYPAD_ROWS; 
const byte COLS = KEYPAD_COLS; 

// 2. Define the key map
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// 3. Define the pins (Based on your description: D5 to D12)
byte rowPins[ROWS] = {KEYPAD_R1, KEYPAD_R2, KEYPAD_R3, KEYPAD_R4}; 
byte colPins[COLS] = {KEYPAD_C1, KEYPAD_C2, KEYPAD_C3, KEYPAD_C4};

// 4. Create the global Keypad object, hidden inside this cpp file
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void InputManager::init() {
    // The Keypad library initializes itself, but we keep this for consistency
}

char InputManager::getPressedKey() {
    return customKeypad.getKey();
}