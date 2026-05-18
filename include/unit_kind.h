#pragma once

enum class UnitKind {Power, Prefer, None};

UnitKind parseUnitKind(const char* unitKindString);
