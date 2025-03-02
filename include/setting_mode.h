#pragma once

enum class SettingMode {Off, On, Cycle, Daily, Weekly};

SettingMode parseSettingMode(int mode);