#pragma once
#include "time_stamp.h"


struct TimeRange
{
    TimeStamp begin_time_;
    TimeStamp end_time_;
};


bool isDay (TimeRange schedule, TimeStamp some_time);
bool inHourAndMinute (TimeRange schedule, TimeStamp some_time);
bool inTimeRange (TimeRange schedule, TimeStamp some_time);