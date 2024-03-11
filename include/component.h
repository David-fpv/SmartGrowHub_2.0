#pragma once

#include <string>  

class Component
{
private:
    std::string type_;
    double value_;
    std::string unit_;

public:
    Component(std::string type, double value, std::string unit);

    std::string GetType() const;
    void SetType(std::string type);

    double GetValue() const;
    void SetValue(double value);

    std::string GetUnit() const;
    void SetUnit(std::string unit);
};