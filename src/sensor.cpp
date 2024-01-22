#include "sensor.h"

SensorData::SensorData(int sensor_id, int pin, std::string type, double value, std::string unit)
{
    sensor_id_ = sensor_id;
    pin_ = pin;
    type_ = type;
    value_ = value;
    unit_ = unit;
}

int SensorData::GetSensorId() const
{
    return sensor_id_;
}

void SensorData::SetSensorId(int sensor_id)
{
    sensor_id_ = sensor_id;
}


int SensorData::GetPin() const
{
    return pin_;
}

void SensorData::SetPin(int pin)
{
    pin_ = pin;
}


std::string SensorData::GetType() const
{
    return type_;
}

void SensorData::SetType(std::string type)
{
    type_ = type;
}


double SensorData::GetValue() const
{
    return value_;
}

void SensorData::SetValue(double value)
{
    value_ = value;
}


std::string SensorData::GetUnit() const
{
    return unit_;
}

void SensorData::SetUnit(std::string unit)
{
    unit_ = unit;
}