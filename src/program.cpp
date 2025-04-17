#include "program.h"


Program::Program()
{
    strcpy(type_, "-");
    strcpy(version_id_, "-");
    mode_ = SettingMode::Off;
    count_entries_ = 0;
}


Program::Program(char* type, char* version_id, SettingMode mode, Entry* entries, int count_entries)
{
    strcpy(type_, type);
    strcpy(version_id_, version_id);
    mode_ = mode;
    count_entries_ = count_entries;

    for (int i = 0; i < count_entries_; i++)
    {
        entries_[i] = entries[i];
    }
}


Program::Program(const Program &p)
{
    strcpy(type_, p.type_);
    strcpy(version_id_, p.type_);
    mode_ = p.mode_;
    count_entries_ = p.count_entries_;

    for (int i = 0; i < count_entries_; i++)
    {
        entries_[i] = p.entries_[i];
    }
}


void Program::Reset(const Program &p)
{
    strcpy(type_, p.type_);
    strcpy(version_id_, p.type_);
    mode_ = p.mode_;
    count_entries_ = p.count_entries_;

    for (int i = 0; i < count_entries_; i++)
    {
        entries_[i] = p.entries_[i];
    }
}


std::string Program::GetType() const
{
    return type_;
}


std::string Program::GetVersionId() const
{
    return version_id_;
}


SettingMode Program::GetMode() const
{
    return mode_;
}


const Entry* Program::GetEntries() const
{
    return entries_;
}

const int Program::GetCountEntries() const
{
    return count_entries_;
}