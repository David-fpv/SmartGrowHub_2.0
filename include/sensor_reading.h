#pragma once
#include <string>
#include "sensor_info.h"

/*char sensor_type[][16] {
    "Methane",
    "Smoke",
    "Hydrogen",
    "AirTemperature",
    "AirPressure",
    "AirHumidity",
    "PlantHeight",
    "SoilAcidity",
    "SoilMoisture",
    "SoilTemperature",
    "Illumination"
};*/

class SensorReading
{
private: 
    int sensor_id_;
    std::string type_;
    double value_;
    std::string unit_;

public:
    SensorReading(int sensor_id, std::string type, double value, std::string unit);
    SensorReading(SensorInfo sensor_info);

    int GetSensorId() const;
    std::string GetType() const;
    double GetValue() const;
    std::string GetUnit() const;
    
};