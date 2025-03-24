#include "setting.h"


Setting::Setting(std::string type, void (*function) (Program program, TimeStamp time_now), Program program)
{
    type_ = type;
    module_function_ = function;
    program_ = program;
}


std::string Setting::GetType() const
{
    return type_;
}


void Setting::SetProgram(Program program)
{
    program_ = program;
}


Program Setting::GetProgram() const
{
    return program_;
}


void Setting::adjust()
{
    module_function_(program_, getTimeStamp());
}