#include "unit_kind.h"

UnitKind parseUnitKind(std::string unitKindString) {
    if (unitKindString == "power") {
        return UnitKind::Power;
    } else if (unitKindString == "prefer") {
        return UnitKind::Prefer;
    }
    
    return UnitKind::None;
}