#pragma once

#include "Arduino.h"
#include <ArduinoJson.h>
#include "program.h"
#include "entry.h"
#include "time_stamp.hpp"
#include "time_range.h"
#include "quantity.h"
#include "sensor_handler.h"
#include "string.h"

class JsonHandler
{
    public:
        std::string getJsonSensorsData(std::vector<SensorReading>);
        Program parseProgram(std::string json);
        //void getJsonSettings();        

    private:
        Entry parseEntry(JsonObject& json_entry);
        TimeStamp getTimeStamp(std::string time_stamp_string);
        TimeRange parseTimeRange(JsonObject& json_time_range);
        Quantity parseQuantity(JsonObject& json_quantity);
};
