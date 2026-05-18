#include "setting_handler.h"

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
            return settings_[i].ChangeScheduleUnit(operate, unit);
    }
    Serial.println("ChangeScheduleUnit: non-existent setting");
    return false;
}

bool SettingHandler::SetMode(ModuleType type, SettingMode mode)
{
    for (uint8_t i = 0; i < count_; i++)
    {
        if (type == settings_[i].GetType())
            return settings_[i].SetMode(mode);
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
