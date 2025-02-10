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