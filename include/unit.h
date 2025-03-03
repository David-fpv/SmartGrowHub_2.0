#pragma once


enum class Unit {Percent = 1, Celsius, Unknown};


Unit toUnit(int unit_id);