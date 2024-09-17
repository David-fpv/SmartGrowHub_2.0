#include "sensor_reading.h"

SensorReading::SensorReading(int sensor_id, std::string type, double value, std::string unit)
{
    sensor_id_ = sensor_id;
    type_ = type;
    value_ = value;
    unit_ = unit;
}

int SensorReading::GetSensorId() const
{
    return sensor_id_;
}

std::string SensorReading::GetType() const
{
    return type_;
}

double SensorReading::GetValue() const
{
    return value_;
}

std::string SensorReading::GetUnit() const
{
    return unit_;
}