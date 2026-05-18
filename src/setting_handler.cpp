#include "setting_handler.h"
#include <LittleFS.h>
#include <ArduinoJson.h>

void SettingHandler::AddSetting(Setting setting)
{
    if (count_ >= MAX_SETTINGS) {
        Serial.println("AddSetting: handler full");
        return;
    }
    settings_[count_++] = setting;
}

bool SettingHandler::ChangeScheduleUnit(ModuleType type, const char* operate, ScheduleUnit unit)
{
    for (uint8_t i = 0; i < count_; i++)
    {
        if (type == settings_[i].GetType())
        {
            bool ok = settings_[i].ChangeScheduleUnit(operate, unit);
            if (ok) saveModule(i);
            return ok;
        }
    }
    Serial.println("ChangeScheduleUnit: non-existent setting");
    return false;
}

bool SettingHandler::SetMode(ModuleType type, SettingMode mode)
{
    for (uint8_t i = 0; i < count_; i++)
    {
        if (type == settings_[i].GetType())
        {
            bool ok = settings_[i].SetMode(mode);
            if (ok) saveModule(i);
            return ok;
        }
    }
    Serial.println("SetMode: non-existent setting");
    return false;
}

void SettingHandler::CurateSetting(ModuleType type)
{
    for (uint8_t i = 0; i < count_; i++)
    {
        if (settings_[i].GetType() == type)
        {
            settings_[i].adjust();
            break;
        }
    }
}

void SettingHandler::CurateAllSetting()
{
    for (uint8_t i = 0; i < count_; i++)
        settings_[i].adjust();
}


void SettingHandler::save()
{
    for (uint8_t i = 0; i < count_; i++)
        saveModule(i);
}

void SettingHandler::load()
{
    for (uint8_t i = 0; i < count_; i++)
        loadModule(i);
}


void SettingHandler::saveModule(uint8_t i)
{
    const char* name = moduleTypeToString(settings_[i].GetType());

    char path[32];
    snprintf(path, sizeof(path), "/%s.json", name);

    File f = LittleFS.open(path, "w");
    if (!f) {
        Serial.printf("saveModule: can't open %s\n", path);
        return;
    }

    StaticJsonDocument<2048> doc;
    doc["mode"] = (int)settings_[i].GetMode();
    JsonArray sched = doc.createNestedArray("schedule");

    ScheduleUnitView units = settings_[i].GetSchedule().GetScheduleUnits();
    for (uint8_t j = 0; j < units.count; j++)
    {
        const ScheduleUnit& u = units.data[j];
        TimeRange  tr  = u.GetTimeInterval();
        Quantity   qty = u.GetQuantity();

        JsonObject entry = sched.createNestedObject();
        entry["id"]   = u.GetUnitId();
        entry["kind"] = (int)u.GetUnitKind();
        entry["d1"]   = (int)tr.begin_time_.day_;
        entry["h1"]   = tr.begin_time_.hour_;
        entry["m1"]   = tr.begin_time_.minutes_;
        entry["d2"]   = (int)tr.end_time_.day_;
        entry["h2"]   = tr.end_time_.hour_;
        entry["m2"]   = tr.end_time_.minutes_;
        entry["mag"]  = qty.magnitude_;
        entry["unit"] = (int)qty.unit_;
    }

    serializeJsonPretty(doc, f);
    f.close();
    Serial.printf("saveModule: saved %s\n", path);
}


void SettingHandler::loadModule(uint8_t i)
{
    const char* name = moduleTypeToString(settings_[i].GetType());

    char path[32];
    snprintf(path, sizeof(path), "/%s.json", name);

    if (!LittleFS.exists(path)) return;

    File f = LittleFS.open(path, "r");
    if (!f) {
        Serial.printf("loadModule: can't open %s\n", path);
        return;
    }

    StaticJsonDocument<2048> doc;
    DeserializationError err = deserializeJson(doc, f);
    f.close();

    if (err) {
        Serial.printf("loadModule: parse error in %s: %s\n", path, err.c_str());
        return;
    }

    settings_[i].SetMode((SettingMode)doc["mode"].as<int>());

    for (JsonObject entry : doc["schedule"].as<JsonArray>())
    {
        const char* uid = entry["id"].as<const char*>();
        UnitKind kind   = (UnitKind)entry["kind"].as<int>();

        TimeStamp begin = { (Day)entry["d1"].as<int>(),
                             entry["h1"].as<int>(),
                             entry["m1"].as<int>() };
        TimeStamp end   = { (Day)entry["d2"].as<int>(),
                             entry["h2"].as<int>(),
                             entry["m2"].as<int>() };
        TimeRange interval = { begin, end };
        Quantity  qty = { entry["mag"].as<int>(), (Unit)entry["unit"].as<int>() };

        ScheduleUnit unit(uid ? uid : "", kind, interval, qty);
        settings_[i].ChangeScheduleUnit("add", unit);
    }

    Serial.printf("loadModule: loaded %s\n", path);
}
