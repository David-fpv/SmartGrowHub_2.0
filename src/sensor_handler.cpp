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
        if (sensors_[i].GetSensorId() == sensor_id)
        {
            return SensorReading(sensors_[i]);
        }
    }
    return SensorReading(-1, "NotFound", 0, "NotFound");
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