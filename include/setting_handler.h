#pragma once

#include <vector>
#include "setting.h"
#include "component.h"
#include "module_functions.h"
//#include "sensor_functions.h"

class SettingHandler
{
public:

    void AddSetting(Setting setting);

    void UpdateSetting(Setting setting);

    Setting GetSetting(std::string type);

    void AddComponentToSetting(std::string type, Component some_component);
    void UpdateComponentToSetting(std::string type, Component some_component);

    void SetStringJson(std::string string_json);

    void CurateSetting(std::string type);

    void CurateAllSetting();

private:
    
    std::vector<Setting> settings_;

};