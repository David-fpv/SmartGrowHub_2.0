#include "unit_kind.h"
#include <string.h>

UnitKind parseUnitKind(const char* unitKindString) {
    if (!unitKindString)                        return UnitKind::None;
    if (strcmp(unitKindString, "power")  == 0)  return UnitKind::Power;
    if (strcmp(unitKindString, "prefer") == 0)  return UnitKind::Prefer;
    return UnitKind::None;
}
