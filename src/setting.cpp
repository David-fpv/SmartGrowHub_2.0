#include "setting.h"

Setting::Setting(std::string type, void (*function) (int))
{
    type_ = type;
    module_function_ = function;
}

std::string Setting::GetType() const
{
    return type_;
}

void Setting::SetType(std::string type)
{
    type_ = type;
}

void Setting::SetFunction(void (*function) (int))
{
    module_function_ = function;
}

void Setting::addComponent(std::string type, double value, std::string unit)
{
    Component new_component(type, value, unit);
    components_.push_back(new_component);
}

void Setting::addComponent(Component new_component)
{
    components_.push_back(new_component);
}

void Setting::updateComponent(std::string type, double value, std::string unit)
{
    for (int i = 0; i < components_.size(); i++)
    {
        if (components_[i].GetType() == type)
        {
            components_[i].SetValue(value);
            components_[i].SetUnit(unit);
            break;
        }
    }

    addComponent(type, value, unit);
}

void Setting::updateComponent(Component some_component)
{
    for (int i = 0; i < components_.size(); i++)
    {
        if (components_[i].GetType() == some_component.GetType())
        {
            components_[i].SetValue(some_component.GetValue());
            components_[i].SetUnit(some_component.GetUnit());
            break;
        }
    }

    addComponent(some_component.GetType(), some_component.GetValue(),some_component.GetUnit());
}


void Setting::adjust()
{
    int mode = -1;
    Serial.println("j");
    
    for (int i = 0; i < components_.size(); i++)
    {
        if (components_[i].GetType() == std::string("Mode"))
        {
            mode = components_[i].GetValue();
            break;
        }
    }

    if (mode == -1)
    {
        return;
    }

    module_function_(mode);
}