#include "program.h"


Program::Program(std::string type, std::string version_id, SettingMode mode, std::vector<Entry> entries)
{
    type_ = type;
    version_id_ = version_id;
    mode_ = mode;
    entries_ = entries;
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


std::vector<Entry> Program::GetEntries() const
{
    return entries_;
}