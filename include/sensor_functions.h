#pragma once
#include <Arduino.h>
#include <TroykaMQ.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

void initialization();
double readHeight();
double readIllumination();
double readSmoke();
double readMethane();
double readHydrogen();
double readAirTemprature();
double readAirHumidity();
double readSoilHumidity();
double readRandomNumber();