#pragma once

#include <string> 
#include "time_range.h"  
#include "quantity.h"

class Entry
{
private:
    TimeRange time_interval_;
    Quantity quantity_;
    

public:
    Entry(TimeRange time_interval, Quantity quantity);
    Entry();

    TimeRange GetTimeInterval() const;
    Quantity GetQuantity() const;
};