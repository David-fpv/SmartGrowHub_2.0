#pragma once
#include <string.h>
#include "sensor_info.h"

/*char sensor_type[][16] {
    "Methane",
    "Smoke",
    "Hydrogen",
    "AirTemperature",
    "AirPressure",
    "AirHumidity",
    "PlantHeight",
    "SoilAcidity",
    "SoilMoisture",
    "SoilTemperature",
    "Illumination"
};*/

class SensorReading
{
private: 
    int sensor_id_;
    char* type_;
    float value_;
    char* unit_;

public:
    SensorReading(int sensor_id, const char* type, float value, const char* unit);
    SensorReading(SensorInfo sensor_info);

    int GetSensorId() const;
    char* GetType() const;
    float GetValue() const;
    char* GetUnit() const;
};