#include "setting.h"

Setting::Setting(std::string type)
{
    type_ = type;
}

std::string Setting::GetType() const
{
    return type_;
}

void Setting::SetType(std::string type)
{
    type_ = type;
}

void Setting::addComponent(std::string type, double value, std::string unit)
{
    Component new_component(type, value, unit);
    components_.push_back(new_component);
}