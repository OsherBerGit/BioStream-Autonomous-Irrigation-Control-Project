#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>
#include "Constants.h"

class DisplayManager {
private:
    LiquidCrystal_I2C lcd;

public:
    DisplayManager() : lcd(LCD_ADDR, LCD_COLS, LCD_ROWS) {}

    void begin() {
        lcd.begin();
        lcd.backlight();
    }

    void showWelcome() {
        lcd.clear();
        lcd.print("BioStream HMI");
    }

    void updateKeyPressed(char key) {
        lcd.setCursor(0, 1);
        lcd.print("Pressed: ");
        lcd.print(key);
        lcd.print("   "); // Clear artifacts
    }
};

#endif