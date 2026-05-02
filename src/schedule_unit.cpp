#include "schedule_unit.h"

ScheduleUnit::ScheduleUnit(std::string unit_id, UnitKind unit_kind, TimeRange time_interval,Quantity quantity)
{
    unit_id_ = unit_id;
    unit_kind_ = unit_kind;
    time_interval_ = time_interval;
    quantity_ = quantity;
}


std::string ScheduleUnit::GetUnitId() const
{
    return unit_id_;
}


UnitKind ScheduleUnit::GetUnitKind() const
{
    return unit_kind_;
}


TimeRange ScheduleUnit::GetTimeInterval() const
{
    return time_interval_;
}


Quantity ScheduleUnit::GetQuantity() const
{
    return quantity_;
}