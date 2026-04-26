#include "TimeManager.h"

void TimeManager::init() {
    // Attempt to connect to the RTC
    if (!rtc.begin()) {
        Serial.println("ERROR: Couldn't find RTC module!");
        // We don't halt the system here so the rest can still work
        return;
    }

    // Check if the RTC lost power and needs its time set
    if (!rtc.isrunning()) {
        Serial.println("RTC is NOT running! Setting initial time...");
        // This sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

String TimeManager::getCurrentTimeString() {
    DateTime now = rtc.now();
    
    // Create a formatted string like "14:30"
    char buffer[10];
    sprintf(buffer, "%02d:%02d", now.hour(), now.minute());
    
    return String(buffer);
}

int TimeManager::getCurrentHour() {
    DateTime now = rtc.now();
    return now.hour();
}