#include "module_functions.h"

#define PIN_LED 2

void initialization_module()
{
    pinMode(PIN_LED, OUTPUT);
}

void blink(SettingMode mode)
{
    if (mode == SettingMode::Off)
    {
        digitalWrite(PIN_LED, 0);
    }
    else if (mode == SettingMode::On)
    {
        int time = millis() % 2000 / 1000;
        digitalWrite(PIN_LED, time);
    }
}

void nothing(int mode)
{

}
