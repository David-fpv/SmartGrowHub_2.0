#pragma once

#include <vector>
#include <ArduinoJson.h>
#include "setting.h"
#include "component.h"
//#include "sensor_functions.h"

class SettingHandler
{
public:

    void SetStringJson(std::string string_json);

    void AddSetting(Setting setting);

    void UpdateSetting(Setting new_setting);

    void CurateSetting();

    void CurateAllSetting();

    Setting GetSetting(std::string type);

private:
    
    std::vector<Setting> settings_;

};