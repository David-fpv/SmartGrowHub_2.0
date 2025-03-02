#pragma once


enum class Unit {Percent = 1, Celsius, Unknown};


Unit parseUnit(int unit_id);