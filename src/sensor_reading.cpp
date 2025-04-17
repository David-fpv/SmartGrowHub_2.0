#include "sensor_reading.h"

SensorReading::SensorReading(int sensor_id, const char* type, float value, const char* unit)
{
    sensor_id_ = sensor_id;
    strcpy(type_, type_);
    value_ = value;
    strcpy(unit_, unit);
}

SensorReading::SensorReading(SensorInfo sensor_info)
{
    sensor_id_ = sensor_info.GetSensorId();
    type_ = sensor_info.GetType();
    value_ = sensor_info.GetValue();
    unit_ = sensor_info.GetUnit();
}

int SensorReading::GetSensorId() const
{
    return sensor_id_;
}

char* SensorReading::GetType() const
{
    return type_;
}

float SensorReading::GetValue() const
{
    return value_;
}

char* SensorReading::GetUnit() const
{
    return unit_;
}