#pragma once

#include "Arduino.h"
#include <ArduinoJson.h>
#include "program.h"
#include "entry.h"
#include "time_stamp.h"
#include "time_range.h"
#include "quantity.h"
#include "sensor_handler.h"
#include "string.h"

class JsonHandler
{
    public:
        char* getJsonSensorsData(std::vector<SensorReading>);
        Program parseProgram(const char* json, uint16_t length);
        //void getJsonSettings();        

    private:
        Entry parseEntry(const JsonObject& json_entry);
        TimeStamp getTimeStamp(std::string time_stamp_string);
        TimeRange parseTimeRange(const JsonObject& json_time_range);
        Quantity parseQuantity(const JsonObject& json_quantity);
        
        char json_str_output_[10]; // Надо больше!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};
