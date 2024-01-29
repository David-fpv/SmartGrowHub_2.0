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

void SensorReading::SetSensorId(int sensor_id)
{
    sensor_id_ = sensor_id;
}


std::string SensorReading::GetType() const
{
    return type_;
}

void SensorReading::SetType(std::string type)
{
    type_ = type;
}


double SensorReading::GetValue() const
{
    return value_;
}

void SensorReading::SetValue(double value)
{
    value_ = value;
}


std::string SensorReading::GetUnit() const
{
    return unit_;
}

void SensorReading::SetUnit(std::string unit)
{
    unit_ = unit;
}