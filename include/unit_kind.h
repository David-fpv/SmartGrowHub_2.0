#pragma once
#include <string>

enum class UnitKind {Power, Prefer, None};

UnitKind parseUnitKind(std::string unitKindString);