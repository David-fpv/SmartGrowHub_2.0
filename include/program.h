#pragma once

#include <string.h>
#include "setting_mode.h"
#include "entry.h"
#include "time_range.h"
#include "Arduino.h"


class Program
{
private:   
    char type_[20];
    char version_id_[30];    // Version ID settings
    SettingMode mode_;
    Entry entries_[10];
    int count_entries_;

public:
    Program(char* type, char* version_id, SettingMode mode, Entry* entries, int count_entries);
    Program(); // delete
    Program(const Program &old_program);
    void Reset(const Program &old_program);

    std::string GetType() const;
    std::string GetVersionId() const;
    SettingMode GetMode() const;
    const Entry* GetEntries() const;
    const int GetCountEntries() const;
};