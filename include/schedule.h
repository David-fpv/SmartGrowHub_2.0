#pragma once

#include <string>
#include <vector>
#include "setting_mode.h"
#include "schedule_unit.h"
#include "time_range.h"
#include "Arduino.h"


class Schedule
{
private:
    std::vector<ScheduleUnit> schedule_units_;

public:
    Schedule();

    bool addScheduleUnit(ScheduleUnit newUnit);
    bool deleteScheduleUnit(std::string unitId);
    std::vector<ScheduleUnit> GetScheduleUnits() const;
};