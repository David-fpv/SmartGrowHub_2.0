#include "sensor_info.h"
#include <string.h>

SensorInfo::SensorInfo() : sensor_id_(-1), function_(nullptr)
{
    type_[0] = '\0';
    unit_[0] = '\0';
}

SensorInfo::SensorInfo(int sensor_id, const char* type, const char* unit, float (*function)())
    : sensor_id_(sensor_id), function_(function)
{
    strncpy(type_, type, sizeof(type_) - 1); type_[sizeof(type_) - 1] = '\0';
    strncpy(unit_, unit, sizeof(unit_) - 1); unit_[sizeof(unit_) - 1] = '\0';
}

int         SensorInfo::GetSensorId() const { return sensor_id_; }
const char* SensorInfo::GetType()     const { return type_; }
const char* SensorInfo::GetUnit()     const { return unit_; }
float       SensorInfo::GetValue()    const { return function_ ? function_() : 0.0f; }
