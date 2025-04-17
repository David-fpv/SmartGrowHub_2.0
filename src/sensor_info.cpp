#include "sensor_info.h"

SensorInfo::SensorInfo(int sensor_id, const char* type, const  char* unit, float (*function) ())
{
    sensor_id_ = sensor_id;
    strcpy(type_, type);
    strcpy(unit_, unit);
    function_ = function;
}


int SensorInfo::GetSensorId()
{
    return sensor_id_;
}


char* SensorInfo::GetType()
{
    return type_;
}


char* SensorInfo::GetUnit()
{
    return unit_;
}


float SensorInfo::GetValue()
{
    return function_();
}