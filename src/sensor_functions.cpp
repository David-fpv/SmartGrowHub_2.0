#include "sensor_functions.h"


GyverBME280 bme;
MicroDS3231 rtc;
GyverDS18Single ds(PIN_SOIL_TEMPERATURE);

void initialization_sensors()
{
    //rtc.setTime(COMPILE_TIME);
    
    if (!bme.begin(0x76))
    {
      Serial.println("Error BME280!");
    }

    pinMode(PIN_HC_TRIG, OUTPUT); // trig выход
    pinMode(PIN_HC_ECHO, INPUT);  // echo вход
  
    ds.requestTemp(); // первый запрос на измерение ds18b20
  
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


float readSoilTemprature() // возможно надо переделать вызов и принятие измерений (хрогологический порядок)
{
  if (ds.ready())
  { // измерения готовы по таймеру
    if (ds.readTemp())
    { // если чтение успешно
      return ds.getTemp();
    }
    ds.requestTemp(); // запрос следующего измерения
  }
  return 0;
}


float readSoilMoisture()
{
  return analogRead(PIN_SOIL_MOISTURE) / 40.95;
}


float readLight()
{
  return analogRead(PIN_LIGHT_SENSOR) / 40.95;
}


void printTime() // ????????????????????????????????
{
  // получаем и выводим каждый элемент отдельно
  Serial.print(rtc.getHours());
  Serial.print(":");
  Serial.print(rtc.getMinutes());
  Serial.print(":");
  Serial.print(rtc.getSeconds());
  Serial.print(" ");
  Serial.print(rtc.getDay());
  Serial.print(" ");
  Serial.print(rtc.getDate());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.println(rtc.getYear());

  // выводим температуру модуля
  Serial.println(rtc.getTemperatureFloat());

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
