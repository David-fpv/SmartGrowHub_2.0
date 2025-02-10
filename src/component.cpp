#include "component.h"

Component::Component(std::string type, TimeRange time, double value, std::string unit)
{
    type_ = type;
    time_ = time;
    value_ = value;
    unit_ = unit;   
}

std::string Component::GetType() const
{
    return type_;
}

void Component::SetType(std::string type)
{
    type_ = type;
}


TimeRange Component::GetTime() const
{
    return time_;
} 

void Component::SetTime (TimeRange time)
{
    time_ = time;
}


double Component::GetValue() const
{
    return value_;
}

void Component::SetValue(double value)
{
    value_ = value;
}


std::string Component::GetUnit() const
{
    return unit_;
}

void Component::SetUnit(std::string unit)
{
    unit_ = unit;
}