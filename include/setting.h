#pragma once

#include <string>
#include <vector>
#include "entry.h"
#include "time_range.h"
#include "Arduino.h"


enum class SettingMode {Off, On, Cycle, Daily, Weekly};


class Setting
{
private:
    std::string type_;          // Module type (name)
    std::string version_id_;    // Version ID settings
    SettingMode mode_;
    std::vector<Entry> entries_;
    void (*module_function_) (int mode);

public:
    Setting(std::string type, void (*function) (int), SettingMode mode_ = {SettingMode::Off});

    std::string GetType() const;

    int GetVersionId() const;
    void SetVersionId(int mode);

    int GetMode() const;
    void SetMode(int mode);

    void addEntry(Entry new_entry);
    void updateEntry(std::string entry_id, Entry updated_entry);
    void deleteEntry(std::string entry_id);

    void adjust();
};