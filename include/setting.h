#pragma once

#include "Arduino.h"
#include "setting_mode.h"
#include "module_functions.h"
#include "sensor_functions.h"
#include "schedule.h"
#include "schedule_unit.h"
#include "time_range.h"
#include "time_stamp.h"
#include "module_type.h"


class Setting
{
private:
    ModuleType  type_;
    SettingMode mode_;
    Schedule    schedule_;
    void (*module_function_)(Setting setting, TimeStamp time_now);

public:
    Setting();
    Setting(ModuleType type, SettingMode mode,
            void (*function)(Setting setting, TimeStamp time_now),
            uint8_t schedule_limit = MAX_SCHEDULE_UNITS);

    ModuleType      GetType()     const;
    SettingMode     GetMode()     const;
    bool            SetMode(SettingMode mode);
    const Schedule& GetSchedule() const;
    bool            ChangeScheduleUnit(const char* operate, ScheduleUnit unit);

    void adjust();
};
