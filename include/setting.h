#pragma once

#include <string>
#include <vector>
#include "component.h"
#include "sensor.h"

class Setting
{
private:
    std::string type_;
    std::vector<Component> components_;
    std::vector<SensorData> sensors_data_;

public:
    Setting(std::string type);

    std::string GetType() const;
    void SetType(std::string type);

    void addComponent(std::string type, double value, std::string unit);

    void addSensorData(int sensor_id, int pin, std::string type, double value, std::string unit);
};