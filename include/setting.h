#pragma once

#include "Arduino.h"
#include <string>
#include <vector>
#include "module_functions.h"
#include "sensor_functions.h"
#include "schedule.h"
#include "schedule_unit.h"
#include "time_range.h"
#include "time_stamp.h"


class Setting
{
private:
    std::string type_;          // Module type (example: "heaterComponent")
    SettingMode mode_;
    Schedule schedule_;
    void (*module_function_) (Setting setting, TimeStamp time_now);

public:
    Setting(std::string type, SettingMode mode, void (*function) (Setting setting, TimeStamp time_now));

    std::string GetType() const;
    SettingMode GetMode() const;
    bool SetMode(SettingMode mode);
    Schedule GetSchedule() const;
    bool ChangeScheduleUnit(std::string operate, ScheduleUnit unit);

    void adjust();
};