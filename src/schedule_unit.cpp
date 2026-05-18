#include "schedule_unit.h"
#include <string.h>

ScheduleUnit::ScheduleUnit()
    : unit_kind_(UnitKind::None), time_interval_{}, quantity_{0, Unit::Unknown}
{
    unit_id_[0] = '\0';
}

ScheduleUnit::ScheduleUnit(const char* unit_id, UnitKind unit_kind, TimeRange time_interval, Quantity quantity)
    : unit_kind_(unit_kind), time_interval_(time_interval), quantity_(quantity)
{
    strncpy(unit_id_, unit_id ? unit_id : "", sizeof(unit_id_) - 1);
    unit_id_[sizeof(unit_id_) - 1] = '\0';
}

const char* ScheduleUnit::GetUnitId()       const { return unit_id_; }
UnitKind    ScheduleUnit::GetUnitKind()     const { return unit_kind_; }
TimeRange   ScheduleUnit::GetTimeInterval() const { return time_interval_; }
Quantity    ScheduleUnit::GetQuantity()     const { return quantity_; }
