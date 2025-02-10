#include "json_handler.h"

String JsonHandler::getJsonSensorsData(std::vector<SensorReading> current_sensor_readings)
{
    DynamicJsonDocument json(1024);

    for (int i = 0; i < current_sensor_readings.size(); i++)
    {
        json[i]["SensorId"] = current_sensor_readings[i].GetSensorId();
        json[i]["Type"] = current_sensor_readings[i].GetType();
        json[i]["Value"] = current_sensor_readings[i].GetValue();
        json[i]["Unit"] = current_sensor_readings[i].GetUnit();
    }

    String string_json;
    serializeJson(json, string_json);
    return string_json;
}