#include "setting_mode.h"


SettingMode parseSettingMode(int mode)
{
    switch (mode)
    {
    case 0: return SettingMode::Off;
    case 1: return SettingMode::On;
    case 2: return SettingMode::Auto;
    case 3: return SettingMode::Daily;
    default: return SettingMode::None;
    }
}