#pragma once

#include <string>
#include <vector>
#include "program.h"
#include "entry.h"
#include "time_range.h"
#include "Arduino.h"


class Setting
{
private:
    std::string type_;          // Module type (example: "heaterComponent")
    Program program_;
    void (*module_function_) (SettingMode mode);

public:
    Setting(std::string type, void (*function) (SettingMode), Program program);

    std::string GetType() const;
    void SetProgram(Program program);
    Program GetProgram() const;

    void adjust();
};