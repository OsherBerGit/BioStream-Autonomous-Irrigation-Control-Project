#pragma once
#include <Arduino.h>
#include <RTClib.h>

/**
 * @class TimeManager
 * @brief Handles communication with the RTC (Real-Time Clock) module via I2C using Dependency Injection.
 */
class TimeManager
{
private:
    // DI: Store a reference to the external RTC object.
    // Note: If using the physical DS3231, this can be easily changed to RTC_DS3231& in the future.
    RTC_DS3231 &rtc;

public:
    /**
     * @brief Constructor injecting the RTC hardware dependency.
     * @param rtcRef Reference to the external RTC object.
     */
    TimeManager(RTC_DS3231 &rtcRef);

    // Initializes the RTC module
    void init();

    // Returns the current time as a formatted string (HH:MM)
    String getCurrentTimeString() const; // Marked const as it doesn't modify state

    // Optional: Get the current hour as an integer for logic checks
    int getCurrentHour() const;
};