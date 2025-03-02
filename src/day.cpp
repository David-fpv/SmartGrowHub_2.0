#include "day.h"


Day parseDay(int dayNumber) {
    switch (dayNumber) {
        case 1: return Day::Monday;
        case 2: return Day::Tuesday;
        case 3: return Day::Wednesday;
        case 4: return Day::Thursday;
        case 5: return Day::Friday;
        case 6: return Day::Saturday;
        case 7: return Day::Sunday;
        default: return Day::AnyDay;
    }
}