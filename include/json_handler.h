#pragma once

#include "Arduino.h"
#include <ArduinoJson.h>
#include "setting_handler.h"
#include "sensor_handler.h"

class JsonHandler
{
public:
    const char* getJsonSensorsData(SensorHandler& handler, const char* device_id);
    const char* getAnswerForMessage(const char* device_id, const char* message_id, int code);
    const char* parseMessage(const uint8_t* data, size_t length,
                             const char* device_id, SettingHandler* modules);

private:
    ScheduleUnit parseScheduleUnit(const JsonObject& json_schedule_unit);
    TimeStamp    getTimeStamp(const char* time_stamp_string);
    TimeRange    parseTimeRange(const JsonObject& json_time_range);
    Quantity     parseQuantity(const JsonObject& json_quantity);
};
