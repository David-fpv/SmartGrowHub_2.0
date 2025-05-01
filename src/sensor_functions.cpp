#include "sensor_functions.h"


GyverBME280 bme;
MicroDS3231 rtc;
GyverNTC therm(PIN_SOIL_TEMPERATURE, 10000, 3950, 25, 10000, 12);

void initialization_sensors()
{
    //rtc.setTime(COMPILE_TIME);
    
    if (!bme.begin(0x76))
    {
      Serial.println("Error BME280!");
    }

    pinMode(PIN_HC_TRIG, OUTPUT); // trig выход
    pinMode(PIN_HC_ECHO, INPUT);  // echo вход
  
    pinMode(PIN_LIGHT_SENSOR, INPUT);
    pinMode(PIN_SOIL_MOISTURE, INPUT);
    pinMode(PIN_SOIL_TEMPERATURE, INPUT);
}


float readRandomNumber()
{
    return random() % 100;
}


float readTemperatureBME()
{
    return bme.readTemperature();
}


float readHumidityBME()
{
    return bme.readHumidity();
}


float readPressureBME()
{
    return bme.readPressure();
}


float readDistance()
{
  // импульс 10 мкс
  digitalWrite(PIN_HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_HC_TRIG, LOW);

  // измеряем время ответного импульса
  uint32_t us = pulseIn(PIN_HC_ECHO, HIGH);

  // считаем расстояние и возвращаем
  float dist = (us / 58.3);
  return dist;
}


float readSoilTemperature()
{
  return therm.getTempAverage();
}


float readSoilMoisture()
{
  return analogRead(PIN_SOIL_MOISTURE) / 40.95;
}


float readLight()
{
  return analogRead(PIN_LIGHT_SENSOR) / 40.95;
}


void printTime()
{
  // выводим дату и время готовыми строками
  Serial.println(rtc.getTimeString());
  Serial.println(rtc.getDateString());
}

TimeStamp getTimeStamp()
{
    TimeStamp time_now;
    time_now.day_ = parseDay(rtc.getDay());
    time_now.hour_ = rtc.getHours();
    time_now.minutes_ = rtc.getMinutes();
    return time_now;
}
