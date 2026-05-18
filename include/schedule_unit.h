#pragma once

#include <Arduino.h>
#include "time_range.h"
#include "unit_kind.h"
#include "quantity.h"

static constexpr int SCHEDULE_UNIT_ID_LEN = 28;

class ScheduleUnit
{
private:
    char      unit_id_[SCHEDULE_UNIT_ID_LEN];
    UnitKind  unit_kind_;
    TimeRange time_interval_;
    Quantity  quantity_;

public:
    ScheduleUnit();
    ScheduleUnit(const char* unit_id, UnitKind unit_kind, TimeRange time_interval, Quantity quantity);

    const char* GetUnitId()       const;
    UnitKind    GetUnitKind()     const;
    TimeRange   GetTimeInterval() const;
    Quantity    GetQuantity()     const;
};
