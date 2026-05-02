#pragma once

#include "Arduino.h"
#include <ArduinoJson.h>
#include "setting_handler.h"
#include "sensor_handler.h"
#include "string.h"

class JsonHandler
{
    public:
        std::string getJsonSensorsData(std::vector<SensorReading>);
        std::string getAnswerForMessage(std::string device_id, std::string message_id, int code);
        std::string parseMessage(std::string json, std::string device_id, SettingHandler *modules);
        //void getJsonSettings();        

    private:
        ScheduleUnit parseScheduleUnit(const JsonObject& json_schedule_unit);
        TimeStamp getTimeStamp(std::string time_stamp_string);
        TimeRange parseTimeRange(const JsonObject& json_time_range);
        Quantity parseQuantity(const JsonObject& json_quantity);
};
