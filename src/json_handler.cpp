#include "json_handler.h"


std::string JsonHandler::getJsonSensorsData(std::vector<SensorReading> current_sensor_readings)
{
    JsonDocument json;

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
    timestamp.day = parseDay(std::stoi(time_stamp_string.substr(0, 2)));
    timestamp.hour = std::stoi(time_stamp_string.substr(3, 2));
    timestamp.minutes = std::stoi(time_stamp_string.substr(6, 2));

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
    quantity.unit_ = parseUnit(json_quantity["unit"].as<int>());
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

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        // Обработка ошибки десериализации
        Serial.print("Ошибка десериализации: ");
        Serial.println(error.c_str());
        return Program("", "", SettingMode(), {}); // Возвращаем пустой объект Program в случае ошибки
    }

    type = doc["type"].as<std::string>();
    version_id = doc["id"].as<std::string>();
    mode = parseSettingMode(doc["mode"].as<int>());

    JsonArray entries_json_array = doc["entries"].as<JsonArray>();
    for (const JsonVariant item : entries_json_array)
    {
        entries.push_back(parseEntry(item));
    }

    return Program(type, version_id, mode, entries);
}