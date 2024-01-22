#include "setting.h"

Setting::Setting(std::string type)
{
    type_ = type;
}

std::string Setting::GetType() const
{
    return type_;
}

void Setting::SetType(std::string type)
{
    type_ = type;
}

void Setting::addComponent(std::string type, double value, std::string unit)
{
    Component new_component(type, value, unit);
    components_.push_back(new_component);
}

void Setting::addSensorData(int sensor_id, int pin, std::string type, double value, std::string unit)
{
    SensorData new_sensor_data(sensor_id, pin, type, value, unit);
    sensors_data_.push_back(new_sensor_data);
}