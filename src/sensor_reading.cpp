#include "sensor_reading.h"

SensorReading::SensorReading(int sensor_id, std::string type, double value, std::string unit)
{
    sensor_id_ = sensor_id;
    type_ = type;
    value_ = value;
    unit_ = unit;
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