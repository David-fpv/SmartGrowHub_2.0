#pragma once

enum class SettingMode {Off, On, Auto, Daily, None};

SettingMode parseSettingMode(int mode);