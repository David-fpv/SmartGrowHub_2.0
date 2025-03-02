#pragma once


enum class Unit {Percent = 1, Celsius, Unknown};


struct Quantity {
    int magnitude_;
    Unit unit_;
};


Unit parseUnit(int unit_id) {
    switch (unit_id) {
        case 1: return Unit::Percent;
        case 2: return Unit::Celsius;
        default: return Unit::Unknown;
    }
}

