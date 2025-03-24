#pragma once

#include <Arduino.h>
#include <microDS3231.h>
#include <ESP32Servo.h>
#include "sensor_functions.h"
#include "program.h"
#include "entry.h"
#include "setting_mode.h"
#include "time_range.h"
#include "time_stamp.h"

#define PIN_LED 2
#define PIN_SERVO 23

#define PIN_TRANSISTOR_1 19
#define PIN_TRANSISTOR_2 18
#define PIN_TRANSISTOR_3 2
#define PIN_TRANSISTOR_4 15
#define PIN_TRANSISTOR_5 14
#define PIN_TRANSISTOR_6 27
#define PIN_TRANSISTOR_7 26


void initialization_module();

void blink(Program program, TimeStamp time_now);
void servo (Program program, TimeStamp time_now);

void transistor_1 (Program program, TimeStamp time_now);
void transistor_2 (Program program, TimeStamp time_now);
void transistor_3 (Program program, TimeStamp time_now);
void transistor_4 (Program program, TimeStamp time_now);
void transistor_5 (Program program, TimeStamp time_now);
void transistor_7 (Program program, TimeStamp time_now);