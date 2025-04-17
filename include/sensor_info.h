#pragma once
#include <string.h>

class SensorInfo
{
private: 

    int sensor_id_;
    char* type_;
    char* unit_;
    float (*function_) ();


public:

    SensorInfo(int sensor_id, const char* type, const char* unit, float (*function) ());

    int GetSensorId();
    char* GetType();
    char* GetUnit();
    float GetValue();
};