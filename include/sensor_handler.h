#pragma once

#include <string.h>
#include <vector>
#include "sensor_reading.h"
#include "sensor_info.h"
#include "sensor_functions.h"


class SensorHandler
{
public: 

    SensorHandler();
    void initialization();
    
    void addSensorInfo(SensorInfo sensor);
    SensorReading getReading(int sensor_id);
    std::vector<SensorReading> getAllReadings();


private:

    std::vector<SensorInfo> sensors_;
};