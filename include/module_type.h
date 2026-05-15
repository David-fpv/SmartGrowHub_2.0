#pragma once

#include <string>

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

inline ModuleType moduleTypeFromString(const std::string& s) {
    if (s == "led")        return ModuleType::Led;
    if (s == "dayLight")   return ModuleType::DayLight;
    if (s == "uvLight")    return ModuleType::UvLight;
    if (s == "heater")     return ModuleType::Heater;
    if (s == "humidifier") return ModuleType::Humidifier;
    if (s == "fan")        return ModuleType::Fan;
    if (s == "waterPump")  return ModuleType::WaterPump;
    if (s == "airFlap")    return ModuleType::AirFlap;
    return ModuleType::Unknown;
}

inline std::string moduleTypeToString(ModuleType type) {
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
