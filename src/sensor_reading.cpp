#include "sensor_reading.h"
#include <string.h>

SensorReading::SensorReading() : sensor_id_(-1), value_(0.0f)
{
    type_[0] = '\0';
    unit_[0] = '\0';
}

SensorReading::SensorReading(int sensor_id, const char* type, float value, const char* unit)
    : sensor_id_(sensor_id), value_(value)
{
    strncpy(type_, type, sizeof(type_) - 1); type_[sizeof(type_) - 1] = '\0';
    strncpy(unit_, unit, sizeof(unit_) - 1); unit_[sizeof(unit_) - 1] = '\0';
}

SensorReading::SensorReading(const SensorInfo& si)
    : sensor_id_(si.GetSensorId()), value_(si.GetValue())
{
    strncpy(type_, si.GetType(), sizeof(type_) - 1); type_[sizeof(type_) - 1] = '\0';
    strncpy(unit_, si.GetUnit(), sizeof(unit_) - 1); unit_[sizeof(unit_) - 1] = '\0';
}

int         SensorReading::GetSensorId() const { return sensor_id_; }
const char* SensorReading::GetType()     const { return type_; }
float       SensorReading::GetValue()    const { return value_; }
const char* SensorReading::GetUnit()     const { return unit_; }
