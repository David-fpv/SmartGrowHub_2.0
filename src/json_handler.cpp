#include "json_handler.h"


std::string JsonHandler::getJsonSensorsData(std::vector<SensorReading> current_sensor_readings)
{
    StaticJsonDocument<1000> json;

    for (int i = 0; i < current_sensor_readings.size(); i++)
    {
        json[i]["SensorId"] = current_sensor_readings[i].GetSensorId();
        json[i]["Type"] = current_sensor_readings[i].GetType();
        json[i]["Value"] = current_sensor_readings[i].GetValue();
        json[i]["Unit"] = current_sensor_readings[i].GetUnit();
    }

    std::string string_json;
    serializeJson(json, string_json);
    return string_json;
}


std::string JsonHandler::getAnswerForMessage(std::string device_id, std::string message_id, int code)
{
    StaticJsonDocument<200> json;

    json["device_id"] = device_id;
    json["message_id"] = message_id;
    json["code"] = code;

    std::string string_json;
    serializeJson(json, string_json);
    return string_json;
}


TimeStamp JsonHandler::getTimeStamp(std::string time_stamp_string)
{    
    TimeStamp timestamp;
    timestamp.day_ = parseDay(std::stoi(time_stamp_string.substr(0, 2)));
    timestamp.hour_ = std::stoi(time_stamp_string.substr(3, 2));
    timestamp.minutes_ = std::stoi(time_stamp_string.substr(6, 2));
    return timestamp;
}


TimeRange JsonHandler::parseTimeRange(const JsonObject& json_time_range)
{
    TimeRange time_range;
    time_range.begin_time_ = getTimeStamp(json_time_range["start"].as<std::string>());
    time_range.end_time_ = getTimeStamp(json_time_range["end"].as<std::string>());
    return time_range;
}


Quantity JsonHandler::parseQuantity(const JsonObject& json_quantity)
{
    Quantity quantity;
    quantity.magnitude_ = json_quantity["magnitude"].as<int>();
    quantity.unit_ = toUnit(json_quantity["unit"].as<int>());
    return quantity;
}


ScheduleUnit JsonHandler::parseScheduleUnit(const JsonObject& json_schedule_unit)
{
    std::string shedule_unit_id = json_schedule_unit["schedule_unit_id"].as<std::string>();
    UnitKind kind               = parseUnitKind(json_schedule_unit["kind"].as<std::string>());
    TimeRange interval          = parseTimeRange(json_schedule_unit["interval"].as<JsonObject>());
    Quantity quantity           = parseQuantity(json_schedule_unit["quantity"].as<JsonObject>());
    
    return ScheduleUnit(shedule_unit_id, kind, interval, quantity);
}

std::string JsonHandler::parseMessage(std::string json, std::string device_id, SettingHandler *modules)
{
    std::string message_id;
    SettingMode mode;
    std::string action;
    ModuleType type;

    // OUPUT_CODES:
    //  2 - Success set ScheduleUnit
    //  1 - Success set mode
    // -1 - Can't set mode
    // -2 - Can't set ScheduleUnit (delete/add)
    // -3 - Wrong device_id
    // -4 - Deserilization error

    StaticJsonDocument<600> doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        std::string message = getAnswerForMessage(device_id, "000000", -4);
        Serial.print("Deserialization error: ");
        Serial.println(error.c_str());
        return message; // Deserialization error handling
    }

    if (doc["device_id"].as<std::string>() != device_id)
    {
        message_id = doc["message_id"].as<std::string>();
        std::string message = getAnswerForMessage(device_id, message_id, -3);

        Serial.println("parseMessage: unsuitable identification number");
        return message;
    }

    message_id  =   doc["message_id"].as<std::string>();
    mode        =   parseSettingMode(doc["mode"].as<int>());
    action      =   doc["action"].as<std::string>();
    type        =   moduleTypeFromString(doc["type"].as<std::string>());

    int code = 0;

    if (mode == SettingMode::None)
    {
        ScheduleUnit unit = parseScheduleUnit(doc["schedule_unit"].as<JsonObject>());
        code = modules->ChangeScheduleUnit(type, action, unit) ? 2 : -2;
        std::string message = getAnswerForMessage(device_id, message_id, code);
        return message;
    }

    code = modules->SetMode(type, mode) ? 1 : -1;
    std::string message = getAnswerForMessage(device_id, message_id, code);
    return message;
}