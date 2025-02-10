#pragma once

#include <string> 
#include "time_range.h"  

class Component
{
private:
    std::string type_;
    TimeRange time_;
    double value_;
    std::string unit_;

public:
    Component(std::string type, TimeRange time, double value, std::string unit);

    std::string GetType() const;
    void SetType(std::string type);

    TimeRange GetTime() const;  
    void SetTime (TimeRange time);

    double GetValue() const;
    void SetValue(double value);

    std::string GetUnit() const;
    void SetUnit(std::string unit);
};