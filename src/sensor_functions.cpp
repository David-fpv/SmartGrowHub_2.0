#include "sensor_functions.h"

#define PIN_MQ2  34
#define TRIG_PIN 13 // pin for Trig
#define ECHO_PIN 14 // pin for Echo
#define LDR_PIN 26 // пин для светорезистора
#define SOIL_PIN 35 // датчик влажности почвы (water sensor)
#define MIN_VALUE 0 // минимальное значение АЦП
#define MAX_VALUE 4095 // максимальное значение АЦП

Adafruit_AHTX0 aht;
MQ2 mq2(PIN_MQ2);

void initialization_sensors()
{
    mq2.calibrate(3.2);
    aht.begin();
    
    // For HC-04RC
    pinMode(TRIG_PIN, OUTPUT); 
    pinMode(LDR_PIN, INPUT);

}

double readSmoke()
{    
    return static_cast<double>(mq2.readSmoke());
}

double readHydrogen()
{    
    return static_cast<double>(mq2.readHydrogen());
}

double readMethane()
{    
    return static_cast<double>(mq2.readMethane());
}

double readHeight()
{
    int duration, distance;
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration / 58;
    return (double)distance;
}

double readIllumination()
{
    int value = analogRead(LDR_PIN);
    int percentage = map(value, MIN_VALUE, MAX_VALUE, 0, 100);
    return (double)percentage;
}

double readSoilHumidity()
{
    int value = analogRead(SOIL_PIN);
    int percentage = map(value, MIN_VALUE, MAX_VALUE, 0, 100);
    return (double)percentage;
}

double readAirTemprature()
{
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    return temp.temperature; 
}

double readHumidity()
{
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    return temp.relative_humidity; 
}

double readRandomNumber()
{
    return millis() % 1000;
}



