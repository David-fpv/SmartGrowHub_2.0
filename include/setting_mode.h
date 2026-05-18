#pragma once

enum class SettingMode {Off, On, Weekly, Daily, None};

SettingMode parseSettingMode(int mode);