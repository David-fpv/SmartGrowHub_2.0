#include "setting.h"


Setting::Setting(std::string type, SettingMode mode, void (*function) (Setting setting , TimeStamp time_now))
{
    type_ = type;
    mode_ = mode;
    module_function_ = function;
}


std::string Setting::GetType() const
{
    return type_;
}


SettingMode Setting::GetMode() const
{
    return mode_;
}

bool Setting::SetMode(SettingMode mode)
{
    mode_ = mode;
    return true;
}


Schedule Setting::GetSchedule() const
{
    return schedule_;
}


bool Setting::ChangeScheduleUnit(std::string operate, ScheduleUnit unit)
{
    if (operate == "delete")
    {
        return schedule_.deleteScheduleUnit(unit.GetUnitId());
    } 
    else if (operate == "add") 
    {
        return schedule_.addScheduleUnit(unit);
    }
    
    Serial.println("ChangeScheduleUnit: unknown operation");
    return false;
}


void Setting::adjust()
{
    module_function_(*this, getTimeStamp());
}