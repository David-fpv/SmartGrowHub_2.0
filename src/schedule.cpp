#include "schedule.h"


Schedule::Schedule()
{
}

bool Schedule::addScheduleUnit(ScheduleUnit newUnit)
{
    schedule_units_.push_back(std::move(newUnit));
    return true;
}


bool Schedule::deleteScheduleUnit(std::string unitId)
{
    for (auto it = schedule_units_.begin(); it != schedule_units_.end(); ++it)
    {
        if (it->GetUnitId() == unitId)
        {
            schedule_units_.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<ScheduleUnit> Schedule::GetScheduleUnits() const
{
    return schedule_units_;
}