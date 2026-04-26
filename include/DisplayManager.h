#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class DisplayManager {
private:
    LiquidCrystal_I2C lcd;
    
    // Cache variables to prevent flickering
    float lastTemp = -99.0;
    int lastMoisture = -1;
    int lastThreshold = -1;
    int lastLight = -1;
    String lastTime = "";
    String lastInput = "";

    // Using int8_t instead of bool so we can have an "uninitialized" state (-1)
    int8_t lastIsAuto = -1;
    int8_t lastIsPumpOn = -1;
    int8_t lastIsError = -1;

public:
    // Constructor - initializes the LCD object with its I2C address and dimensions
    DisplayManager(uint8_t address, uint8_t cols, uint8_t rows);

    // Initializes the display and turns on the backlight (call inside setup)
    void init();

    // Clear the entire screen
    void clear();

    // Shows the boot sequence welcome message
    void showWelcomeMessage();

    // Updates the input view when user is setting the threshold
    void updateInputView(String currentInput);

    // Row 1: Environmental Data
    void updateTemperature(float temp);
    void updateTime(String timeStr);
    void updateLight(int lightValue);

    // Row 2: System Status
    void updateMoisture(int current, int threshold);
    void updateSystemStatus(bool isAuto, bool isPumpOn, bool isError);
};