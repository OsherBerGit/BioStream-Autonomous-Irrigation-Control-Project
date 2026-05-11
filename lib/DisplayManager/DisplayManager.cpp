#include "DisplayManager.h"

// Constructor with Dependency Injection
DisplayManager::DisplayManager(LiquidCrystal_I2C &lcdReference)
    : lcd(lcdReference) {}

void DisplayManager::init()
{
    lcd.begin();
    lcd.backlight();
}

void DisplayManager::clear()
{
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

void DisplayManager::showWelcomeMessage()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  BIOSTREAM v1  ");
    lcd.setCursor(0, 1);
    lcd.print(" SYSTEM  ONLINE ");

    // Show the welcome message for 2 seconds before clearing the screen for regular updates
    delay(2000);
    lcd.clear(); // This will also call our cache reset above
}

void DisplayManager::updateInputView(String currentInput)
{
    if (currentInput == lastInput)
        return;

    lastInput = currentInput;

    lcd.setCursor(0, 1);
    lcd.print("Set Thr: ");
    lcd.print(currentInput);
    lcd.print("   "); // Clear trailing chars
}

void DisplayManager::updateTemperature(float temp)
{
    if (abs(temp - lastTemp) < 0.1)
        return;

    lastTemp = temp;

    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temp, 1);
    lcd.print("C");
}

void DisplayManager::updateTime(String timeStr)
{
    if (timeStr == lastTime)
        return;

    lastTime = timeStr;

    lcd.setCursor(11, 0);
    lcd.print(timeStr);
}

void DisplayManager::updateLight(int lightValue)
{
    if (lightValue == lastLight)
        return;

    lastLight = lightValue;

    lcd.setCursor(8, 1);
    // Format: L:600 (5 chars)
    lcd.print("L:");

    int displayVal = (lightValue > 999) ? 999 : lightValue;
    lcd.print(displayVal);

    // Padding logic: Clear only what's necessary, NEVER hitting column 13
    if (displayVal < 10)
        lcd.print("  "); // 2 spaces to clear columns 11, 12
    else if (displayVal < 100)
        lcd.print(" "); // 1 space to clear column 12
}

void DisplayManager::updateMoisture(int current, int threshold)
{
    if (current == lastMoisture && threshold == lastThreshold)
        return;

    lastMoisture = current;
    lastThreshold = threshold;

    lcd.setCursor(0, 1);
    // Format: M:30/45 (7 chars)
    lcd.print("M:");
    lcd.print(current);
    lcd.print("/");
    lcd.print(threshold);
}

void DisplayManager::updateSystemStatus(bool isAuto, bool isPumpOn, bool isError)
{
    if (isAuto == lastIsAuto && isPumpOn == lastIsPumpOn && isError == lastIsError)
        return;

    lastIsAuto = isAuto;
    lastIsPumpOn = isPumpOn;
    lastIsError = isError;

    lcd.setCursor(13, 1);
    // Format: A:+ or M:- (3 chars)
    lcd.print(isAuto ? "A" : "M");
    lcd.print(":");

    if (isError)
        lcd.print("E");
    else
        lcd.print(isPumpOn ? "+" : "-");
}