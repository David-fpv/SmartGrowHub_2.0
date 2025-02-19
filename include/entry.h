#pragma once

#include <string> 
#include "time_range.h"  
#include "quantity.h"

class Entry
{
private:
    std::string id_;
    TimeRange time_interval_;
    Quantity quantity_;
    

public:
    Entry(std::string id, TimeRange time_interval, Quantity quantity);

    std::string GetId() const;
    TimeRange GetTimeInterval() const;
    Quantity GetQuantity() const;
};