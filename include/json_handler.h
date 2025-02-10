#pragma once

#include "Arduino.h"
#include "sensor_handler.h"
#include "string.h"

class JsonHandler
{
    public:
        String getJsonSensorsData(std::vector<SensorReading>);
        //void setJsonSettings(String json);
        //void getJsonSettings();        
};
