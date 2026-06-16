#include "json_handler.h"
#include <string.h>
#include <stdlib.h>


const char* JsonHandler::getJsonSensorsData(SensorHandler& handler, const char* device_id)
{
    static char buf[600];
    StaticJsonDocument<1200> json;

    json["device_id"] = device_id;
    JsonArray data = json.createNestedArray("data");

    for (uint8_t i = 0; i < handler.getCount(); i++)
    {
        const SensorInfo& s = handler.getSensor(i);
        JsonObject entry = data.createNestedObject();
        entry["sensor_id"] = s.GetSensorId();
        entry["type"]     = s.GetType();
        entry["value"]    = s.GetValue();
        entry["unit"]     = s.GetUnit();
    }

    serializeJson(json, buf, sizeof(buf));
    return buf;
}


const char* JsonHandler::getAnswerForMessage(const char* device_id, const char* message_id, int code)
{
    static char buf[128];
    StaticJsonDocument<200> json;

    json["device_id"]  = device_id;
    json["message_id"] = message_id ? message_id : "";
    json["code"]       = code;

    serializeJson(json, buf, sizeof(buf));
    return buf;
}


TimeStamp JsonHandler::getTimeStamp(const char* ts)
{
    TimeStamp timestamp = {};
    if (!ts || strlen(ts) < 8)
    {
        Serial.println("getTimeStamp: invalid format");
        return timestamp;
    }
    char part[3] = {};
    strncpy(part, ts,     2); timestamp.day_     = parseDay(atoi(part));
    strncpy(part, ts + 3, 2); timestamp.hour_    = atoi(part);
    strncpy(part, ts + 6, 2); timestamp.minutes_ = atoi(part);
    return timestamp;
}


TimeRange JsonHandler::parseTimeRange(const JsonObject& json_time_range)
{
    TimeRange time_range;
    time_range.begin_time_ = getTimeStamp(json_time_range["start"].as<const char*>());
    time_range.end_time_   = getTimeStamp(json_time_range["end"].as<const char*>());
    return time_range;
}


Quantity JsonHandler::parseQuantity(const JsonObject& json_quantity)
{
    Quantity quantity;
    quantity.magnitude_ = json_quantity["magnitude"].as<int>();
    quantity.unit_      = toUnit(json_quantity["unit"].as<const char*>());
    return quantity;
}


ScheduleUnit JsonHandler::parseScheduleUnit(const JsonObject& json_schedule_unit)
{
    const char* unit_id  = json_schedule_unit["schedule_unit_id"].as<const char*>();
    UnitKind    kind     = parseUnitKind(json_schedule_unit["kind"].as<const char*>());
    TimeRange   interval = parseTimeRange(json_schedule_unit["interval"].as<JsonObject>());
    Quantity    quantity = parseQuantity(json_schedule_unit["quantity"].as<JsonObject>());
    return ScheduleUnit(unit_id ? unit_id : "", kind, interval, quantity);
}


const char* JsonHandler::parseMessage(const uint8_t* data, size_t length,
                                      const char* device_id, SettingHandler* modules)
{
    // OUTPUT CODES:
    //  2 - Success set ScheduleUnit
    //  1 - Success set mode
    // -1 - Can't set mode
    // -2 - Can't set ScheduleUnit (delete/add)
    // -3 - Wrong device_id
    // -4 - Deserialization error

    StaticJsonDocument<800> doc;
    DeserializationError error = deserializeJson(doc, data, length);
    if (error)
    {
        Serial.print("Deserialization error: ");
        Serial.println(error.c_str());
        return getAnswerForMessage(device_id, "000000", -4);
    }

    const char* msg_device_id = doc["device_id"].as<const char*>();
    const char* message_id    = doc["message_id"].as<const char*>();

    if (!msg_device_id || strcmp(msg_device_id, device_id) != 0)
    {
        Serial.print("Device id: ");
        Serial.println(device_id);
        Serial.print("Message device id: ");
        Serial.println(msg_device_id);
        Serial.println("parseMessage: unsuitable identification number");
        return getAnswerForMessage(device_id, message_id ? message_id : "000000", -3);
    }

    SettingMode mode   = parseSettingMode(doc["mode"].as<const char*>());
    const char* action = doc["action"].as<const char*>();
    ModuleType  type   = moduleTypeFromString(doc["type"].as<const char*>());

    int code = 0;

    if (mode == SettingMode::None)
    {
        if (action && strcmp(action, "delete") == 0)
        {
            const char* unit_id = doc["schedule_unit"]["schedule_unit_id"].as<const char*>();
            ScheduleUnit stub(unit_id ? unit_id : "", UnitKind::None, TimeRange{}, Quantity{0, Unit::Unknown});
            code = modules->ChangeScheduleUnit(type, "delete", stub) ? 2 : -2;
        }
        else if (action && strcmp(action, "clearAll") == 0)
        {
            code = modules->DeleteAllScheduleUnits(type) ? 2 : -2;
        }
        else
        {
            ScheduleUnit unit = parseScheduleUnit(doc["schedule_unit"].as<JsonObject>());
            code = modules->ChangeScheduleUnit(type, action ? action : "", unit) ? 2 : -2;
        }
        return getAnswerForMessage(device_id, message_id, code);
    }

    code = modules->SetMode(type, mode) ? 1 : -1;
    return getAnswerForMessage(device_id, message_id, code);
}
