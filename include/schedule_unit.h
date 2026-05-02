#pragma once

#include <string> 
#include "time_range.h"  
#include "unit_kind.h"
#include "quantity.h"

class ScheduleUnit
{
private:
    std::string unit_id_;
    UnitKind unit_kind_;
    TimeRange time_interval_;
    Quantity quantity_;
    

public:
    ScheduleUnit(std::string unit_id, UnitKind unit_kind, TimeRange time_interval, Quantity quantity);

    std::string GetUnitId() const;
    UnitKind GetUnitKind() const;
    TimeRange GetTimeInterval() const;
    Quantity GetQuantity() const;
};