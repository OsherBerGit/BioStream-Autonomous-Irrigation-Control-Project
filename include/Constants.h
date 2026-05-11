#pragma once
#include <Arduino.h>

// ============================================================================
// Hardware Pin Definitions (The Physical Map)
// ============================================================================

// --- Analog Sensors ---
#define PIN_SOIL_MOISTURE A0 // Resistive/Capacitive Soil Moisture Sensor
#define PIN_LDR A1           // Light Dependent Resistor (Light Sensor)
#define PIN_TEMP_SENSOR A2   // NTC Thermistor or LM35

// --- I2C Communication ---
// Note: SDA = A4, SCL = A5 on Arduino Nano/Uno (Hardware I2C pins)
#define LCD_ADDRESS 0x27 // Default I2C address for 16x2 LCD modules

// --- Digital Outputs ---
// ARCHITECTURE NOTE: Using D4 for the relay. D10 cannot be used as it is
// dedicated to the Keypad matrix (KEYPAD_R3).
#define PIN_RELAY_PUMP 4 // Signal pin for the Water Pump Relay

// --- Keypad Matrix Pins (Digital D5 - D12) ---
#define KEYPAD_R1 8
#define KEYPAD_R2 7
#define KEYPAD_R3 6
#define KEYPAD_R4 5
#define KEYPAD_C1 12
#define KEYPAD_C2 11
#define KEYPAD_C3 9
#define KEYPAD_C4 10

// ============================================================================
// System Logic & Thresholds (Business Rules)
// ============================================================================

// ARCHITECTURE NOTE: PUMP_ON and PUMP_OFF macros were intentionally REMOVED.
// The IrrigationManager class now encapsulates the Active-Low/Active-High logic
// internally via Dependency Injection, respecting SOLID principles.

// --- Irrigation Thresholds ---
#define DEFAULT_MOISTURE_THRESHOLD 30 // Default percentage to trigger pump
#define LIGHT_THRESHOLD 600           // Above this value, it's too bright to water (Inhibition)

// --- Keypad Configuration ---
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

// --- Safety Settings ---
#define MAX_PUMP_RUN_TIME 10000 // Maximum continuous pump run time in milliseconds (10s limit)

// --- Climate Thresholds ---
#define TEMP_MIN_FREEZE 5.0    // Below this (Celsius), halt watering to prevent freezing
#define TEMP_MAX_HEATWAVE 35.0 // Above this (Celsius), plants require more water
#define HEATWAVE_BONUS_PCT 10  // Add 10% to the moisture threshold during a heatwave

// ============================================================================
// Display Formatting
// ============================================================================
#define LCD_COLS 16
#define LCD_ROWS 2