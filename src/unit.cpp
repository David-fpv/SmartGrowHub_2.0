#include "unit.h"
#include <string.h>


Unit toUnit(const char* unit_str)
{
    if (!unit_str)                return Unit::Unknown;
    if (strcmp(unit_str, "%") == 0) return Unit::Percent;
    if (strcmp(unit_str, "C") == 0) return Unit::Celsius;
    return Unit::Unknown;
}
