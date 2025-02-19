#include "entry.h"

Entry::Entry(std::string id, TimeRange time_interval, Quantity quantity)
{
    id_ = id;
    time_interval_ = time_interval_;
    quantity_ = quantity;
}

std::string Entry::GetId() const
{
    return id_;
}

TimeRange Entry::GetTimeInterval() const
{
    return time_interval_;
}

Quantity Entry::GetQuantity() const
{
    return quantity_;
}