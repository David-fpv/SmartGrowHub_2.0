#include "sensor_functions.h"

#define PIN_MQ2  A0
#define TRIG_PIN 13 // pin for Trig
#define ECHO_PIN 14 // pin for Echo
#define LDR_PIN 26 // пин для светорезистора
#define MIN_VALUE 0 // минимальное значение АЦП
#define MAX_VALUE 4095 // максимальное значение АЦП


void initialization()
{
    // For MQ2
    /*MQ2 mq2(PIN_MQ2);
    mq2.calibrate(3.2);*/

    // For HC-04RC
    pinMode(TRIG_PIN, OUTPUT); 
    pinMode(LDR_PIN, INPUT);

}

/*void readMQ2()
{
     Serial.print("\tMethane: ");
    Serial.print(mq2.readMethane());
    Serial.print(" ppm");
    Serial.print("\tSmoke: ");
    Serial.print(mq2.readSmoke());
    Serial.print(" ppm");
    Serial.print("\tHydrogen: ");
    Serial.print(mq2.readHydrogen());
    Serial.println(" ppm");
    delay(100);
}*/

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



