#pragma once


enum class Day {AnyDay, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};


typedef struct TimeStamp
{   
    Day day;
    int hour;
    int minutes;
};


typedef struct TimeRange
{
    TimeStamp begin_time_;
    TimeStamp end_time_;
};