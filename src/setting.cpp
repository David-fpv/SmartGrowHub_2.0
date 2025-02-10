#include "setting.h"

Setting::Setting(std::string type, void (*function) (int), int mode)
{
    type_ = type;
    module_function_ = function;
    mode_ = mode;
}

std::string Setting::GetType() const
{
    return type_;
}

int  Setting::GetMode() const
{
    return mode_;
}

void  Setting::SetMode(int mode)
{
    if (mode >= 0 and mode <= 2)
    {
        mode_ = mode;
    }
    else
    {
        throw std::invalid_argument( "An impossible setting operation mode was obtained" );
    }
}

// void Setting::SetType(std::string type)
// {
//     type_ = type;
// }

// void Setting::SetFunction(void (*function) (int))
// {
//     module_function_ = function;
// }

// void Setting::addComponent(std::string type, double value, std::string unit)
// {
//     Component new_component(type, value, unit);
//     components_.push_back(new_component);
// }

void Setting::addComponent(Component new_component)
{
    components_.push_back(new_component);
}

// void Setting::updateComponent(std::string type, double value, std::string unit)
// {
//     for (int i = 0; i < components_.size(); i++)
//     {
//         if (components_[i].GetType() == type)
//         {
//             components_[i].SetValue(value);
//             components_[i].SetUnit(unit);
//             break;
//         }
//     }

//     addComponent(type, value, unit);
// }

void Setting::updateComponent(Component some_component)
{
    for (int i = 0; i < components_.size(); i++)
    {
        if (components_[i].GetType() == some_component.GetType())
        {
            components_[i].SetTime(some_component.GetTime());
            components_[i].SetValue(some_component.GetValue());
            components_[i].SetUnit(some_component.GetUnit());
            break;
        }
    }

    addComponent(some_component);
}


void Setting::adjust()
{
    module_function_(mode_);
}