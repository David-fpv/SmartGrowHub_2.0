#pragma once


enum class Unit {Percent = 1, Celsius, Unknown};


Unit toUnit(const char* unit_str);