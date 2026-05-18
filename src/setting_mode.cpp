#include "setting_mode.h"
#include <string.h>


SettingMode parseSettingMode(const char* mode)
{
    if (!mode)                       return SettingMode::None;
    if (strcmp(mode, "off")    == 0) return SettingMode::Off;
    if (strcmp(mode, "on")     == 0) return SettingMode::On;
    if (strcmp(mode, "weekly") == 0) return SettingMode::Weekly;
    if (strcmp(mode, "daily")  == 0) return SettingMode::Daily;
    return SettingMode::None;
}