#include "setting_handler.h"

void SettingHandler::AddSetting(Setting setting)
{
    settings_.push_back(setting);
}


void  SettingHandler::UpdateSetting(std::string type, Program new_program)
{
    for (int i = 0; i < settings_.size(); i++)
    {
        if (settings_[i].GetType() == setting.GetType())
        {
            settings_[i].SetProgram(new_program);
        }
        break;
    }
}


void SettingHandler::CurateSetting(std::string type)
{
    for (int i = 0; i < settings_.size(); i++)
    {
        if (settings_[i].GetType() == type)
        {
            settings_[i].adjust();
        }
        break;
    }
}


void SettingHandler::CurateAllSetting()
{
    for (int i = 0; i < settings_.size(); i++)
    {
        settings_[i].adjust();
    }
}