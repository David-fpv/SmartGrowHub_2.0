#include "unit.h"

Unit parseUnit(int unit_id) {
    switch (unit_id) {
        case 1: return Unit::Percent;
        case 2: return Unit::Celsius;
        default: return Unit::Unknown;
    }
}