#pragma once
#include <Arduino.h>

// ============================================================================
// Hardware Pin Definitions
// ============================================================================

// --- Analog Sensors ---
#define PIN_SOIL_MOISTURE  A0   // Resistive/Capacitive Soil Moisture Sensor
#define PIN_LDR            A1   // Light Dependent Resistor (Light Sensor)
#define PIN_TEMP_SENSOR    A2   // NTC Thermistor or LM35

// --- I2C Communication (Internal Hardware) ---
// SDA = A4, SCL = A5 on Arduino Nano/Uno
#define LCD_ADDRESS        0x27 // Default I2C address for 16x2 LCD modules

// --- Digital Outputs ---
#define PIN_RELAY_PUMP     4    // Signal pin for the Water Pump Relay

// --- Keypad Matrix Pins (Digital D5 - D12) ---
// These are referenced in InputManager.cpp
#define KEYPAD_R1          12
#define KEYPAD_R2          11
#define KEYPAD_R3          10
#define KEYPAD_R4          9
#define KEYPAD_C1          8
#define KEYPAD_C2          7
#define KEYPAD_C3          6
#define KEYPAD_C4          5

// ============================================================================
// System Logic & Thresholds
// ============================================================================

// --- Relay Logic ---
// Adjusted for simulation/hardware behavior (Active-High)
#define PUMP_ON            HIGH 
#define PUMP_OFF           LOW

// --- Irrigation Thresholds ---
#define DEFAULT_MOISTURE_THRESHOLD 30   // Default percentage to trigger pump
#define LIGHT_THRESHOLD            600  // Above this, it's too bright to water (Inhibition)

// --- Keypad Configuration ---
#define KEYPAD_ROWS        4
#define KEYPAD_COLS        4

// --- Safety Settings ---
#define MAX_PUMP_RUN_TIME 10000 // Maximum continuous run time in milliseconds (10s)

// --- Climate Thresholds ---
#define TEMP_MIN_FREEZE    5.0   // Below this (Celsius), do not water to prevent ice
#define TEMP_MAX_HEATWAVE  35.0  // Above this (Celsius), plants need more water
#define HEATWAVE_BONUS_PCT 10    // Add 10% to moisture threshold during heatwave

// ============================================================================
// Display Formatting
// ============================================================================
#define LCD_COLS           16
#define LCD_ROWS           2