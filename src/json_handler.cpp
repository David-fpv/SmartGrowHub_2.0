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


Entry JsonHandler::parseEntry(const JsonObject& json_entry)
{
    return Entry(parseTimeRange(json_entry["interval"].as<JsonObject>()), parseQuantity(json_entry["quantity"].as<JsonObject>()));
}


Program JsonHandler::parseProgram(std::string json)
{
    std::string type;
    std::string version_id;
    SettingMode mode;
    std::vector<Entry> entries;

    StaticJsonDocument<2000> doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        Serial.print("Deserialization error: ");
        Serial.println(error.c_str());
        return Program("", "", SettingMode::Off, {}); // Deserialization error handling
    }

    type = doc["type"].as<std::string>();
    version_id = doc["version_id"].as<std::string>();
    mode = parseSettingMode(doc["mode"].as<int>());


    JsonArray entries_json_array = doc["entries"].as<JsonArray>();
    for (const JsonVariant item : entries_json_array)
    {
        entries.push_back(parseEntry(item));
    }

    return Program(type, version_id, mode, entries);
}