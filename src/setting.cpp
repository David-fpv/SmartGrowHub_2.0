#include "setting.h"


Setting::Setting(std::string type, void (*function) (int value), int value)
{
    type_ = type;
    module_function_ = function;
    value_ = value;
}


std::string Setting::GetType() const
{
    return type_;
}


void Setting::SetValue(int value)
{
    value_ = value;
}


int Setting::GetValue() const
{
    return value_;
}


void Setting::adjust()
{
    module_function_(value_);
}