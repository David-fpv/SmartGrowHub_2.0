#include "json_handler.h"


std::string JsonHandler::getJsonSensorsData(std::vector<SensorReading> current_sensor_readings)
{
    DynamicJsonDocument json(1024);

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


TimeStamp JsonHandler::getTimeStamp(std::string time_stamp_string)
{    
    TimeStamp timestamp;
    timestamp.day = parseDay(std::stoi(str.substr(0, 2)));
    timestamp.hour = std::stoi(str.substr(3, 2));
    timestamp.minutes = std::stoi(str.substr(6, 2));

    return timestamp;
}


TimeRange JsonHandler::parseTimeRange(JsonObject& json_time_range)
{
    TimeRange time_range;
    time_range.begin_time_ = getTimeStamp(json_time_range["start"]);
    time_range.end_time_ = getTimeStamp(json_time_range["end"]);
    return time_range;
}


Quantity JsonHandler::parseQuantity(JsonObject& json_quantity)
{
    Quantity quantity;
    quantity.magnitude_ = json_quantity["magnitude"];
    quantity.unit_ = json_quantity["unit"];
    return quantity;
}


Entry JsonHandler::parseEntry(JsonObject& json_entry)
{
    return Entry(parseTimeRange(json_entry["interval"]), parseQuantity(json_entry["quantity"]));
}


Program JsonHandler::parseProgram(std::string json)
{
    std::string type;
    std::string version_id;
    SettingMode mode;
    std::vector<Entry> entries;

    JsonDocument doc;
    deserializeJson(doc, json);

    type = doc["type"];
    version_id = doc["id"];
    mode = doc["mode"];

    for (JsonVariant item: doc["entries"])
    {
        entries.push_back(parseEntry(item))
    }

    return Program(type, version_id, mode, entries);
}