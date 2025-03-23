#pragma once
#include "time_stamp.h"


struct TimeRange
{
    TimeStamp begin_time_;
    TimeStamp end_time_;
};


bool isDay (TimeRange schedule, TimeStamp some_time);
bool isHour (TimeRange schedule, TimeStamp some_time);
bool isMinute (TimeRange schedule, TimeStamp some_time);
bool isHourAndMinute (TimeRange schedule, TimeStamp some_time);