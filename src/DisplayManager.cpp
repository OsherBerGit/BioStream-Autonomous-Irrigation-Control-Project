#include "DisplayManager.h"

// Initialization list to pass parameters directly to the LiquidCrystal_I2C object
DisplayManager::DisplayManager(uint8_t address, uint8_t cols, uint8_t rows) 
    : lcd(address, cols, rows) {}

void DisplayManager::init() {
    lcd.begin();
    lcd.backlight();
}

void DisplayManager::clear() {
    lcd.clear();

    // CRITICAL: Reset cache variables so the screen fully redraws after a clear!
    lastTemp = -99.0;
    lastMoisture = -1;
    lastThreshold = -1;
    lastLight = -1;
    lastTime = "";
    lastInput = "";
    lastIsAuto = -1;
    lastIsPumpOn = -1;
    lastIsError = -1;
}

void DisplayManager::showWelcomeMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  BIOSTREAM v1  ");
    lcd.setCursor(0, 1);
    lcd.print(" SYSTEM  ONLINE ");
    delay(2000);
    lcd.clear(); // This will also call our cache reset above
}

void DisplayManager::updateInputView(String currentInput) {
    // Early exit if the input hasn't changed
    if (currentInput == lastInput) return;
    lastInput = currentInput;

    lcd.setCursor(0, 1);
    lcd.print("Set Thr: ");
    lcd.print(currentInput);
    lcd.print("   "); // Clear trailing chars
}

void DisplayManager::updateTemperature(float temp) {
    // Early exit if the change is too small (prevents flickering on minor fluctuations)
    if (abs(temp - lastTemp) < 0.1) return;
    lastTemp = temp;

    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temp, 1);
    lcd.print("C");
}

void DisplayManager::updateTime(String timeStr) {
    // Early exit if the time string is exactly the same
    if (timeStr == lastTime) return;
    lastTime = timeStr;

    lcd.setCursor(11, 0);
    lcd.print(timeStr);
}

void DisplayManager::updateLight(int lightValue) {
    // Early exit if the light value hasn't changed
    if (lightValue == lastLight) return;
    lastLight = lightValue;

    lcd.setCursor(8, 1);
    // Format: L:600 (5 chars)
    lcd.print("L:");
    lcd.print(lightValue);
    lcd.print(" "); // Clear leftovers
}

void DisplayManager::updateMoisture(int current, int threshold) {
    // Early exit if neither the moisture nor the threshold changed
    if (current == lastMoisture && threshold == lastThreshold) return;
    lastMoisture = current;
    lastThreshold = threshold;

    lcd.setCursor(0, 1);
    // Format: M:30/45 (7 chars)
    lcd.print("M:");
    lcd.print(current);
    lcd.print("/");
    lcd.print(threshold);
}

void DisplayManager::updateSystemStatus(bool isAuto, bool isPumpOn, bool isError) {
    // Early exit if none of the status flags changed
    if (isAuto == lastIsAuto && isPumpOn == lastIsPumpOn && isError == lastIsError) return;
    lastIsAuto = isAuto;
    lastIsPumpOn = isPumpOn;
    lastIsError = isError;
    
    lcd.setCursor(13, 1);
    // Format: A:+ or M:- (3 chars)
    lcd.print(isAuto ? "A" : "M");
    lcd.print(":");
    
    if (isError) lcd.print("E");
    else lcd.print(isPumpOn ? "+" : "-");
}