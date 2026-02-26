#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

// --- Analog Sensor Pins ---
const int PIN_LDR      = A0; // Light Dependent Resistor
const int PIN_MOISTURE = A1; // Soil Moisture Sensor
const int PIN_LM35     = A2; // Temperature Sensor

// --- Digital Pins ---
const int PIN_RELAY = 3; // Pump relay pin

// --- Relay Logic (Active Low) ---
const int PUMP_ON  = LOW;
const int PUMP_OFF = HIGH;

// --- Thresholds ---
const int MOISTURE_DRY_LIMIT = 600; // Example: Start pumping if value > 600

// --- ADC Constants ---
const float ADC_VREF = 5.0;
const float ADC_RES  = 1024.0;

// --- LCD Settings ---
const uint8_t LCD_ADDR = 0x27;
const uint8_t LCD_COLS = 16;
const uint8_t LCD_ROWS = 2;

// --- Keypad Settings ---
const byte ROWS = 4;
const byte COLS = 4;

const char KEYS[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

// Adjusted pins to avoid conflict with D10 (Relay) if needed
const byte ROW_PINS[ROWS] = {8, 7, 6, 5};
const byte COL_PINS[COLS] = {12, 11, 4, 9}; // Changed 10 to 4 for the Pump safety

#endif