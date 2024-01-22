#include "component.h"

Component::Component(std::string type, double value, std::string unit)
{
    type_ = type;
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