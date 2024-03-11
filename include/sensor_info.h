#pragma once
#include <string>

class SensorInfo
{
private: 

    int sensor_id_;
    std::string type_;
    std::string unit_;
    double (*function_) ();


public:

    SensorInfo(int sensor_id, std::string type, std::string unit, double (*function) ());

    int GetSensorId();
    std::string GetType();
    std::string GetUnit();
    double GetValue();
};