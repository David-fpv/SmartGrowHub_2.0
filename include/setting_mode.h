#pragma once

enum class SettingMode {Off, On, Cycle, Daily, Weekly};

SettingMode parseSettingMode(int mode)
{
    switch (mode)
    {
    case 0: return SettingMode::Off;
    case 1: return SettingMode::On;
    case 2: return SettingMode::Cycle;
    case 3: return SettingMode::Daily;
    case 4: return SettingMode::Weekly;
    default: return SettingMode::Off;
    }
}