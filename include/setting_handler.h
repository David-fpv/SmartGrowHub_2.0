#pragma once

#include "setting.h"
#include "schedule.h"
#include "schedule_unit.h"
#include "module_functions.h"

static constexpr uint8_t MAX_SETTINGS = 8;

class SettingHandler
{
public:
    void AddSetting(Setting setting);
    bool ChangeScheduleUnit(ModuleType type, const char* operate, ScheduleUnit unit);
    bool SetMode(ModuleType type, SettingMode mode);
    void CurateSetting(ModuleType type);
    void CurateAllSetting();

private:
    Setting settings_[MAX_SETTINGS];
    uint8_t count_ = 0;
};
