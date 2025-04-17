#include "setting.h"


Setting::Setting(const char* type, void (*function) (Program program, TimeStamp time_now), Program program)
{
    strcpy(type_, type);
    module_function_ = function;
    program_.Reset(program);
}


char* Setting::GetType() const
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