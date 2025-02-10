#pragma once

#include <string>
#include <vector>
#include "component.h"
#include "time_range.h"
#include "Arduino.h"

class Setting
{
private:
    std::string type_;
    int mode_;
    void (*module_function_) (int mode);
    std::vector<Component> components_;

public:
    Setting(std::string type, void (*function) (int), int mode_ = 0);

    std::string GetType() const;
    int GetMode() const;
    void SetMode(int mode);
    //void SetType(std::string type);

    //void SetFunction(void (*function) (int)); 

    //void addComponent(std::string type, double value, std::string unit);
    void addComponent(Component new_component);

    //void updateComponent(std::string type, double value, std::string unit);
    void updateComponent(Component some_component);

    void adjust();
};