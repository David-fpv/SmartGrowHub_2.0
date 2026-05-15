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
    bool ChangeScheduleUnit(ModuleType type, std::string operate, ScheduleUnit unit);
    bool SetMode(ModuleType type, SettingMode mode);

    //void SaveJsonSetting(); // Functions for saving and loading settings to esp32 memory
    //void LoadJsonSetting();

    void CurateSetting(ModuleType type);
    void CurateAllSetting(); 

private:
    std::vector<Setting> settings_;

};