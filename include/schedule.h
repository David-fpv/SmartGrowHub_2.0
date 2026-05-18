#pragma once

#include "schedule_unit.h"
#include "time_range.h"
#include "Arduino.h"

static constexpr uint8_t MAX_SCHEDULE_UNITS = 12;

struct ScheduleUnitView {
    const ScheduleUnit* data;
    uint8_t             count;
    const ScheduleUnit* begin() const { return data; }
    const ScheduleUnit* end()   const { return data + count; }
};

class Schedule
{
private:
    ScheduleUnit schedule_units_[MAX_SCHEDULE_UNITS];
    uint8_t      count_;
    uint8_t      limit_;

public:
    Schedule()                   : count_(0), limit_(MAX_SCHEDULE_UNITS) {}
    explicit Schedule(uint8_t limit) : count_(0), limit_(limit < MAX_SCHEDULE_UNITS ? limit : MAX_SCHEDULE_UNITS) {}

    bool             addScheduleUnit(const ScheduleUnit& unit);
    bool             deleteScheduleUnit(const char* unitId);
    ScheduleUnitView GetScheduleUnits() const;
};
