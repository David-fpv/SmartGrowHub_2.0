#include "information.h"

void Information::setValue(int id, std::string type, double value)
{
    for(int i = 0; i < sensors_data_.size(); i++)
    {
        if(id == sensors_data_[i].GetSensorId() && type == sensors_data_[i].GetType())
        {
            sensors_data_[i].SetValue(value);
            break;
        }
    }
}

void Information::addSensorData(int sensor_id, std::string type, std::string unit)
{
    SensorData new_sensor_data(sensor_id, type, unit);
    sensors_data_.push_back(new_sensor_data);
}

String Information::getStringJson()
{
    DynamicJsonDocument json(1024);

    for (int i = 0; i < sensors_data_.size(); i++)
    {
        json[i]["SensorId"] = sensors_data_[i].GetSensorId();
        json[i]["Type"] = sensors_data_[i].GetType();
        json[i]["Value"] = sensors_data_[i].GetValue();
        json[i]["Unit"] = sensors_data_[i].GetUnit();
    }

    
    String jsonString;
    serializeJson(json, jsonString);
    return jsonString;
}