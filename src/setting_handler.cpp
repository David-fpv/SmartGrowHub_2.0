#include "setting_handler.h"

void SettingHandler::AddSetting(Setting setting)
{
    settings_.push_back(setting);
}


bool  SettingHandler::ChangeScheduleUnit(std::string type, std::string operate, ScheduleUnit unit)
{
    for (int i = 0; i < settings_.size(); i++)
    {
        if (type == settings_[i].GetType())
        {
            return settings_[i].ChangeScheduleUnit(operate, unit);
        }
    }

    Serial.println("ChangeScheduleUnit: non-existent setting");
    return false;
}


bool SettingHandler::SetMode(std::string type, SettingMode mode)
{
    for (int i = 0; i < settings_.size(); i++)
    {
        if (type == settings_[i].GetType())
        {
            return settings_[i].SetMode(mode);
        }
    }

    Serial.println("ChangeScheduleUnit: non-existent setting");
    return false;
}


void SettingHandler::CurateSetting(std::string type)
{
    for (int i = 0; i < settings_.size(); i++)
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
    for (int i = 0; i < settings_.size(); i++)
    {
        settings_[i].adjust();
    }
}