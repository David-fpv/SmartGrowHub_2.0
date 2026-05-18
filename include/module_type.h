#pragma once

#include <string.h>

enum class ModuleType {
    Led,
    DayLight,
    UvLight,
    Heater,
    Humidifier,
    Fan,
    WaterPump,
    AirFlap,
    Unknown
};

inline ModuleType moduleTypeFromString(const char* s) {
    if (!s)                           return ModuleType::Unknown;
    if (strcmp(s, "led")        == 0) return ModuleType::Led;
    if (strcmp(s, "dayLight")   == 0) return ModuleType::DayLight;
    if (strcmp(s, "uvLight")    == 0) return ModuleType::UvLight;
    if (strcmp(s, "heater")     == 0) return ModuleType::Heater;
    if (strcmp(s, "humidifier") == 0) return ModuleType::Humidifier;
    if (strcmp(s, "fan")        == 0) return ModuleType::Fan;
    if (strcmp(s, "waterPump")  == 0) return ModuleType::WaterPump;
    if (strcmp(s, "airFlap")    == 0) return ModuleType::AirFlap;
    return ModuleType::Unknown;
}

inline const char* moduleTypeToString(ModuleType type) {
    switch (type) {
        case ModuleType::Led:        return "led";
        case ModuleType::DayLight:   return "dayLight";
        case ModuleType::UvLight:    return "uvLight";
        case ModuleType::Heater:     return "heater";
        case ModuleType::Humidifier: return "humidifier";
        case ModuleType::Fan:        return "fan";
        case ModuleType::WaterPump:  return "waterPump";
        case ModuleType::AirFlap:    return "airFlap";
        default:                     return "unknown";
    }
}
