#include "time_range.h"


bool inDay (TimeRange schedule, TimeStamp some_time)
{
    if (static_cast<int>(schedule.begin_time_.day_) <= static_cast<int>(some_time.day_) && static_cast<int>(some_time.day_) <= static_cast<int>(schedule.end_time_.day_))
    {
        return true;
    }
    return false;
}

bool inHourAndMinute (TimeRange schedule, TimeStamp some_time)
{
    int time_begin = schedule.begin_time_.hour_ * 60 + schedule.begin_time_.minutes_;
    int time_end = schedule.end_time_.hour_ * 60 + schedule.end_time_.minutes_;
    int time_stamp = some_time.hour_ * 60 + some_time.minutes_;

    if (time_begin > time_end)
    {
        time_end += 24 * 60;
        time_stamp += 24 * 60;
    }

    if (time_begin <= time_stamp && time_stamp < time_end)
    {
        return true;
    }
    return false;
}

bool inTimeRange (TimeRange schedule, TimeStamp some_time)
{
    int time_begin = (static_cast<int>(schedule.begin_time_.day_) - 1) * 24 * 60 + schedule.begin_time_.hour_ * 60 + schedule.begin_time_.minutes_;
    int time_end = (static_cast<int>(schedule.end_time_.day_) - 1) * 24 * 60 + schedule.end_time_.hour_ * 60 + schedule.end_time_.minutes_;
    int time_stamp = (static_cast<int>(some_time.day_) - 1) * 24 * 60 + some_time.hour_ * 60 + some_time.minutes_;

    if (time_begin > time_end)
    {
        time_end += 7 * 24 * 60;
        time_stamp += 7 * 24 * 60;
    }

    if (time_begin <= time_stamp && time_stamp < time_end)
    {
        return true;
    }
    return false;
}