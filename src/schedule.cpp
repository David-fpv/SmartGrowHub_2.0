#include "schedule.h"
#include <string.h>

bool Schedule::addScheduleUnit(const ScheduleUnit& unit)
{
    if (count_ >= limit_) {
        Serial.println("addScheduleUnit: schedule full");
        return false;
    }
    schedule_units_[count_++] = unit;
    return true;
}

bool Schedule::deleteScheduleUnit(const char* unitId)
{
    for (uint8_t i = 0; i < count_; i++)
    {
        if (strcmp(schedule_units_[i].GetUnitId(), unitId) == 0)
        {
            for (uint8_t j = i; j < count_ - 1; j++)
                schedule_units_[j] = schedule_units_[j + 1];
            count_--;
            return true;
        }
    }
    return false;
}

ScheduleUnitView Schedule::GetScheduleUnits() const
{
    return {schedule_units_, count_};
}
