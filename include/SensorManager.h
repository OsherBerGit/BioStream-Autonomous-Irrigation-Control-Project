#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Constants.h"

class SensorManager {
public:
    // Constructor
    SensorManager() {}

    // Returns raw light value (0 - 1023)
    // 0 is very dark, 1023 is very bright
    int readLight();

    // Returns raw value from soil moisture sensor (0-1023)
    int readMoisture();

    // Returns temperature in Celsius using LM35 formula
    float readTemperature();
};

#endif