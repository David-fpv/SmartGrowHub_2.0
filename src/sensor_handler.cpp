#include "sensor_handler.h"


SensorHandler::SensorHandler(void (*initialization_function) ())
{
    initialization_function_ = initialization_function;
}


void SensorHandler::initialization()
{
    initialization_function_();
}


void SensorHandler::addSensorInfo(SensorInfo sensor)
{
    sensors_.push_back(sensor);
}


SensorReading SensorHandler::getReading(int sensor_id, std::string type)
{
    for (int i = 0; i < sensors_.size(); i++)
    {
        if (sensor_id == sensors_[i].GetSensorId() && type == sensors_[i].GetType())
        {
            return SensorReading(sensors_[i].GetSensorId(), sensors_[i].GetType(), sensors_[i].GetValue(), sensors_[i].GetUnit());
        }
    }
}


std::vector<SensorReading> SensorHandler::getAllReadings()
{
    std::vector<SensorReading> all_readings;

    for (int i = 0; i < sensors_.size(); i++)
    {
        all_readings.push_back(SensorReading(sensors_[i].GetSensorId(), sensors_[i].GetType(), sensors_[i].GetValue(), sensors_[i].GetUnit()));
    }

    return all_readings;
}

String SensorHandler::getStringJson()
{
    DynamicJsonDocument json(1024);

    for (int i = 0; i < sensors_.size(); i++)
    {
        json[i]["SensorId"] = sensors_[i].GetSensorId();
        json[i]["Type"] = sensors_[i].GetType();
        json[i]["Value"] = sensors_[i].GetValue();
        json[i]["Unit"] = sensors_[i].GetUnit();
    }

    String jsonString;
    serializeJson(json, jsonString);
    return jsonString;
}