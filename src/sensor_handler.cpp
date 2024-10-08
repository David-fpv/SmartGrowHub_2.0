#include "sensor_handler.h"


SensorHandler::SensorHandler()
{
}


void SensorHandler::initialization()
{
    initialization();
}


void SensorHandler::addSensorInfo(SensorInfo sensor)
{
    sensors_.push_back(sensor);
}


SensorReading SensorHandler::getReading(int sensor_id)
{
    for (int i = 0; i < sensors_.size(); i++)
    {
        if (sensor_id == sensors_[i].GetSensorId())
        {
            return SensorReading(sensors_[i]);
        }
    }
}


std::vector<SensorReading> SensorHandler::getAllReadings()
{
    std::vector<SensorReading> all_readings;

    for (int i = 0; i < sensors_.size(); i++)
    {
        all_readings.push_back(SensorReading(sensors_[i]));
    }

    return all_readings;
}

String SensorHandler::getStringJson()
{
    DynamicJsonDocument json(1024);

    for (int i = 0; i < sensors_.size(); i++)
    {
        SensorReading sensor = SensorReading(sensors_[i]);

        json[i]["SensorId"] = sensor.GetSensorId();
        json[i]["Type"] = sensor.GetType();
        json[i]["Value"] = sensor.GetValue();
        json[i]["Unit"] = sensor.GetUnit();
    }

    String string_json;
    serializeJson(json, string_json);
    return string_json;
}