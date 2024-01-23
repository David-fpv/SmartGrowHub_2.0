#pragma once

#include <string>
#include <vector>
#include "sensor.h"
#include "data_collection.h"
#include <ArduinoJson.h>

class Information
{
private:
    std::vector<SensorData> sensors_data_;

public:

    void setValue(int id, std::string type, double value);    

    void addSensorData(int sensor_id, std::string type, std::string unit);

    String getStringJson();
};