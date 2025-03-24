#pragma once
#include <Arduino.h>
#include <GyverBME280.h>
#include <microDS3231.h>
#include <GyverDS18.h>
#include "time_stamp.h"


#define PIN_HC_TRIG 33
#define PIN_HC_ECHO 25

#define PIN_LIGHT_SENSOR 35
#define PIN_SOIL_MOISTURE 34
#define PIN_SOIL_TEMPERATURE 32


void initialization_sensors();
float readRandomNumber();
float readTemperatureBME();
float readHumidityBME();
float readPressureBME();
float readDistance();
float readSoilTemprature();
float readSoilMoisture();
float readLight();
void printTime();
TimeStamp getTimeStamp();