#include "sensor_handler.h"

SensorHandler::SensorHandler() : count_(0) {}

void SensorHandler::addSensorInfo(const SensorInfo& sensor)
{
    if (count_ >= MAX_SENSORS) {
        Serial.println("addSensorInfo: handler full");
        return;
    }
    sensors_[count_++] = sensor;
}

SensorReading SensorHandler::getReading(int sensor_id) const
{
    for (uint8_t i = 0; i < count_; i++)
    {
        if (sensors_[i].GetSensorId() == sensor_id)
            return SensorReading(sensors_[i]);
    }
    return SensorReading(-1, "NotFound", 0.0f, "NotFound");
}
