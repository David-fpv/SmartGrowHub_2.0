#pragma once

#include <string>
#include <vector>
#include "sensor_reading.h"
#include "sensor_info.h"
#include <ArduinoJson.h>


class SensorHandler
{
public: 

    SensorHandler(void (*initialization_function) ());

    void initialization();

    void addSensorInfo(SensorInfo sensor);

    SensorReading getReading(int sensor_id, std::string type);

    std::vector<SensorReading> getAllReadings();

    String getStringJson();


private:

    void (*initialization_function_) ();

    std::vector<SensorInfo> sensors_;
};