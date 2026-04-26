#pragma once
#include <Arduino.h>
#include <RTClib.h>

/**
 * @class TimeManager
 * @brief Handles communication with the RTC (Real-Time Clock) module via I2C.
 */
class TimeManager {
private:
    // Wokwi uses DS1307 by default. If using a physical DS3231, change to RTC_DS3231.
    RTC_DS1307 rtc; 

public:
    // Initializes the RTC module
    void init();

    // Returns the current time as a formatted string (HH:MM)
    String getCurrentTimeString();
    
    // Optional: Get the current hour as an integer for logic checks
    int getCurrentHour();
};