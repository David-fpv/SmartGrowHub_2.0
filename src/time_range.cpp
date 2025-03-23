#include "time_range.h"


bool isDay (TimeRange schedule, TimeStamp some_time)
{
    if (schedule.begin_time_.day_ < some_time.day_ && some_time.day_ < schedule.end_time_.day_)
    {
        return true;
    }
    return false;
}


bool isHour (TimeRange schedule, TimeStamp some_time)
{
    if (schedule.begin_time_.hour_ < some_time.hour_ && some_time.hour_ < schedule.end_time_.hour_)
    {
        return true;
    }
    return false;
}


bool isMinute (TimeRange schedule, TimeStamp some_time)
{
    if (schedule.begin_time_.minutes_ < some_time.minutes_ && some_time.minutes_ < schedule.end_time_.minutes_)
    {
        return true;
    }
    return false;
}


bool isHourAndMinute (TimeRange schedule, TimeStamp some_time)
{
    if (isHour(schedule, some_time) && isMinute(schedule, some_time))
    {
        return true;
    }
    return false;
}