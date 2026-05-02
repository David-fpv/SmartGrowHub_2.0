#pragma once

#include <vector>
#include "setting.h"
#include "schedule.h"
#include "schedule_unit.h"
#include "module_functions.h"
//#include "sensor_functions.h"

class SettingHandler
{
public:

    void AddSetting(Setting setting);
    bool ChangeScheduleUnit(std::string type, std::string operate, ScheduleUnit unit);
    bool SetMode(std::string type, SettingMode mode);

    //void SaveJsonSetting(); // Functions for saving and loading settings to esp32 memory
    //void LoadJsonSetting(); 

    void CurateSetting(std::string type);
    void CurateAllSetting(); 

private:
    std::vector<Setting> settings_;

};