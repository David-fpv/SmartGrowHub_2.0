#pragma once

#include <string>
#include <vector>
#include "entry.h"
#include "time_range.h"
#include "Arduino.h"


enum class SettingMode {Off, On, Cycle, Daily, Weekly};


class Program
{
private:   
    std::string type_;
    std::string version_id_;    // Version ID settings
    SettingMode mode_;
    std::vector<Entry> entries_;

public:
    Program(std::string version_id, SettingMode mode, std::vector<Entry> entries);

    std::string GetType() const;
    std::string GetVersionId() const;
    SettingMode GetMode() const;
    std::vector<Entry> GetEntries() const;
};