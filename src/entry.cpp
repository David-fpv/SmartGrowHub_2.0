#include "entry.h"

Entry::Entry(TimeRange time_interval, Quantity quantity)
{
    time_interval_ = time_interval;
    quantity_ = quantity;
}


TimeRange Entry::GetTimeInterval() const
{
    return time_interval_;
}


Quantity Entry::GetQuantity() const
{
    return quantity_;
}