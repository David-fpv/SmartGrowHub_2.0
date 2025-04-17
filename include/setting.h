#pragma once

#include "Arduino.h"
#include "module_functions.h"
#include "program.h"
#include "entry.h"
#include "time_range.h"
#include "time_stamp.h"


class Setting
{
private:
    char* type_;          // Module type (example: "heaterComponent")
    Program program_;
    void (*module_function_) (Program program, TimeStamp time_now);

public:
    Setting(const char* type, void (*function) (Program program, TimeStamp time_now), Program program);

    char* GetType() const;
    void SetProgram(Program program);
    Program GetProgram() const;

    void adjust();
};