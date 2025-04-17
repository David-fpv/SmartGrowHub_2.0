#include "json_handler.h"


char* JsonHandler::getJsonSensorsData(std::vector<SensorReading> current_sensor_readings)
{
    StaticJsonDocument<100> json; // Надо больше!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    for (int i = 0; i < current_sensor_readings.size(); i++)
    {
        json[i]["SensorId"] = current_sensor_readings[i].GetSensorId();
        json[i]["Type"] = current_sensor_readings[i].GetType();
        json[i]["Value"] = current_sensor_readings[i].GetValue();
        json[i]["Unit"] = current_sensor_readings[i].GetUnit();
    }

    serializeJson(json, json_str_output_, sizeof(json_str_output_));
    return json_str_output_;
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


Program JsonHandler::parseProgram(const char* json, uint16_t length)
{
    char type[20];
    char version_id[30];
    SettingMode mode;

    Entry entries[10];
    int count_entries = 0;

    StaticJsonDocument<4000> json_doc;
    DeserializationError error = deserializeJson(json_doc, json);

    if (error)
    {
        Serial.print("Deserialization error: ");
        Serial.println(error.c_str());
        return Program(); // Deserialization error handling
    }

    strcpy(type, json_doc["type"]);
    strcpy(version_id, json_doc["version_id"]);
    mode = parseSettingMode(json_doc["mode"].as<int>());

    for (int i = 0; i < json_doc["entries"].size(), i < sizeof(entries)/sizeof(entries[0]); i++)
    {
        entries[i] = parseEntry(json_doc["entries"][i]);
        count_entries++;
    }

    return Program(type, version_id, mode, entries, count_entries);
}