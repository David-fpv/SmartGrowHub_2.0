#include "setting.h"
#include <string.h>

Setting::Setting()
    : type_(ModuleType::Unknown), mode_(SettingMode::Off), module_function_(nullptr)
{}

Setting::Setting(ModuleType type, SettingMode mode, void (*function)(Setting, TimeStamp), uint8_t schedule_limit)
    : type_(type), mode_(mode), schedule_(schedule_limit), module_function_(function)
{}

ModuleType      Setting::GetType()     const { return type_; }
SettingMode     Setting::GetMode()     const { return mode_; }
bool            Setting::SetMode(SettingMode mode) { mode_ = mode; return true; }
const Schedule& Setting::GetSchedule() const { return schedule_; }

bool Setting::ChangeScheduleUnit(const char* operate, ScheduleUnit unit)
{
    if (strcmp(operate, "delete") == 0)
        return schedule_.deleteScheduleUnit(unit.GetUnitId());
    if (strcmp(operate, "add") == 0)
        return schedule_.addScheduleUnit(unit);
    Serial.println("ChangeScheduleUnit: unknown operation");
    return false;
}

void Setting::DeleteAllScheduleUnits()
{
    schedule_.deleteAllScheduleUnits();
}

void Setting::adjust()
{
    if (module_function_)
        module_function_(*this, getTimeStamp());
}
