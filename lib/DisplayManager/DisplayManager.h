#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

/**
 * @class DisplayManager
 * @brief Handles display output for the irrigation system using Dependency Injection.
 */
class DisplayManager
{
private:
    // Reference to the LiquidCrystal_I2C object
    LiquidCrystal_I2C &lcd;

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
    // (Dependency Injection)
    DisplayManager(LiquidCrystal_I2C &lcdReference);

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