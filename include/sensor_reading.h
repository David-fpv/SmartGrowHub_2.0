#pragma once

#include "sensor_info.h"

class SensorReading
{
private:
    int   sensor_id_;
    char  type_[20];
    float value_;
    char  unit_[8];

public:
    SensorReading();
    SensorReading(int sensor_id, const char* type, float value, const char* unit);
    SensorReading(const SensorInfo& sensor_info);

    int         GetSensorId() const;
    const char* GetType()     const;
    float       GetValue()    const;
    const char* GetUnit()     const;
};
