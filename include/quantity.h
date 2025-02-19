#pragma once
#include "string"


enum class Units {Percent, Celsius};


typedef struct Quantity {
    int magnitude_;
    Units unit;
};