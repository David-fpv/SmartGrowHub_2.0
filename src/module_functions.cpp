#include "module_functions.h"

#define PIN_LED 2

void initialization_module()
{
    pinMode(PIN_LED, OUTPUT);
}

void blink(int mode)
{
    if (mode == 0)
    {
        digitalWrite(PIN_LED, 0);
    }
    else if (mode == 1)
    {
        int time = millis() % 2000 / 1000;
        digitalWrite(PIN_LED, time);
    }
    else if (mode == 2)
    {

    }
}

void nothing(int mode)
{

}
