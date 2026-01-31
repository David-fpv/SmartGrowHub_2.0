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
#define PIN_TRANSISTOR_3 4
#define PIN_TRANSISTOR_4 2
#define PIN_TRANSISTOR_5 14
#define PIN_TRANSISTOR_6 27
#define PIN_TRANSISTOR_7 26


void initialization_module();

void blink(int value);
void servo (int value);

void transistor_1 (int value);
void transistor_2 (int value);
void transistor_3 (int value);
void transistor_4 (int value);
void transistor_5 (int value);
void transistor_7 (int value);