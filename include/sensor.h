#pragma once

#include <string>

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

class SensorData
{
private:
    int sensor_id_;
    std::string type_;
    double value_;
    std::string unit_;

public:
    SensorData(int sensor_id, std::string type, double value, std::string unit);

    int GetSensorId() const;
    void SetSensorId(int sensor_id);

    std::string GetType() const;
    void SetType(std::string type);

    double GetValue() const;
    void SetValue(double value);

    std::string GetUnit() const;
    void SetUnit(std::string unit);
};