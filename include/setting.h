#pragma once

#include "Arduino.h"
#include <string>
#include <vector>
#include "module_functions.h"
#include "program.h"
#include "entry.h"
#include "time_range.h"
#include "time_stamp.h"


class Setting
{
private:
    std::string type_;          // Module type (example: "heaterComponent")
    int value_;
    void (*module_function_) (int value); // example 0-255, 0 - off, 255 - on

public:
    Setting(std::string type, void (*function) (int value), int value);

    std::string GetType() const;
    void SetValue(int value);
    int GetValue() const;

    void adjust();
};