#pragma once

#include <vector>
#include "program.h"
#include "setting.h"
#include "entry.h"
#include "module_functions.h"
//#include "sensor_functions.h"

class SettingHandler
{
public:

    void AddSetting(Setting setting);
    void SetProgram(Program program);

    //void SaveJsonSetting(); // Functions for saving and loading settings to esp32 memory
    //void LoadJsonSetting(); 

    void CurateSetting(char* type);
    void CurateAllSetting(); 

private:
    std::vector<Setting> settings_;

};