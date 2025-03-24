#pragma once


enum class Unit {Percent = 1, Quantity, Celsius, Unknown};


Unit toUnit(int unit_id);