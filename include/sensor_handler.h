#pragma once

#include <string>
#include <vector>
#include "sensor_reading.h"
#include "data_collection.h"
#include <ArduinoJson.h>


class SensorHandler
{
public: 

    SensorReading getReading(std::string);

    SensorReading *getAllReadings();

    void addSensorData();

    //String getStringJson();

private:

    std::vector<SensorReading> sensors_;
};