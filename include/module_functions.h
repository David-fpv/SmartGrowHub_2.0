#pragma once

#include <Arduino.h>
#include <microDS3231.h>
#include <ESP32Servo.h>
#include "sensor_functions.h"
#include "setting.h"
#include "time_range.h"

#define PIN_LED 2
#define PIN_SERVO 23

#define PIN_TRANSISTOR_1 19
#define PIN_TRANSISTOR_2 18
#define PIN_TRANSISTOR_3 4
#define PIN_TRANSISTOR_4 2
#define PIN_TRANSISTOR_5 14
#define PIN_TRANSISTOR_6 27
#define PIN_TRANSISTOR_7 26

class Setting; // Forward declaration

void initialization_module();

void blink(Setting setting, TimeStamp time_some);
void servo (Setting setting, TimeStamp time_now);

void day_light_module_function (Setting setting, TimeStamp time_now);
void transistor_2 (Setting setting, TimeStamp time_now);
void transistor_3 (Setting setting, TimeStamp time_now);
void transistor_4 (Setting setting, TimeStamp time_now);
void transistor_5 (Setting setting, TimeStamp time_now);
void transistor_7 (Setting setting, TimeStamp time_now);