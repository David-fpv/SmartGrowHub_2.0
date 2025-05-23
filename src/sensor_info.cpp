#include "sensor_info.h"

SensorInfo::SensorInfo(int sensor_id, std::string type, std::string unit, float (*function) ())
{
    sensor_id_ = sensor_id;
    type_ = type;
    function_ = function;
    unit_ = unit;
}


int SensorInfo::GetSensorId()
{
    return sensor_id_;
}


std::string SensorInfo::GetType()
{
    return type_;
}


float SensorInfo::GetValue()
{
    return function_();
}


std::string SensorInfo::GetUnit()
{
    return unit_;
}