#include "module_functions.h"


Servo myservo;


void initialization_module()
{
    pinMode(PIN_TRANSISTOR_1, OUTPUT);
    pinMode(PIN_TRANSISTOR_2, OUTPUT);
    pinMode(PIN_TRANSISTOR_3, OUTPUT);
    pinMode(PIN_TRANSISTOR_4, OUTPUT);
    pinMode(PIN_TRANSISTOR_5, OUTPUT);
    pinMode(PIN_TRANSISTOR_6, OUTPUT);
    pinMode(PIN_TRANSISTOR_7, OUTPUT);

    digitalWrite(PIN_TRANSISTOR_1, LOW);
    digitalWrite(PIN_TRANSISTOR_2, LOW);
    digitalWrite(PIN_TRANSISTOR_3, LOW);
    digitalWrite(PIN_TRANSISTOR_4, LOW);
    digitalWrite(PIN_TRANSISTOR_5, LOW);
    digitalWrite(PIN_TRANSISTOR_6, LOW);
    digitalWrite(PIN_TRANSISTOR_7, LOW);

    myservo.attach(PIN_SERVO);
    delay(500);
}


void blink(int value)
{
    int pin = PIN_LED;
    digitalWrite(pin, value);
}


void servo_on_off (int mode)
{
    static int angle = 10;
    if (mode > 0 && angle < 80)
    {
        while(angle < 80)
        {
            angle++;
            myservo.write(angle);
            delay(10); 
        }
    }
    
    if (mode == 0 && angle > 20)
    {
        while(angle > 20)
        {
            angle--;
            myservo.write(angle);
            delay(10);
        }
    }
}


void servo (int value) // AirFlap
{
    servo_on_off(value);
}


void transistor_1 (int value) // Daylight
{
    int pin = PIN_TRANSISTOR_1;
    digitalWrite(pin, value);
}


void transistor_2 (int value) // Phyto lighting
{
    int pin = PIN_TRANSISTOR_2;
    digitalWrite(pin, value);
}


void transistor_3 (int value) // Heater
{
    int pin = PIN_TRANSISTOR_3;
    int inaccuracy = 2;
    float (*sensor_function) () = readTemperatureBME;

    if ((float)value - sensor_function() > inaccuracy && value != 0)
    {
        digitalWrite(pin, HIGH);
    }
    else
    {
        digitalWrite(pin, LOW);
    }
}


void transistor_4 (int value) // Air humidifier
{
    int pin = PIN_TRANSISTOR_4;
    int inaccuracy = 2;
    float (*sensor_function) () = readHumidityBME;

    if ((float)value - sensor_function() > inaccuracy && value != 0)
    {
        digitalWrite(pin, HIGH);
    }
    else
    {
        digitalWrite(pin, LOW);
    }
}


void transistor_5 (int value) // Fan
{
    int pin = PIN_TRANSISTOR_5;
    digitalWrite(pin, value);
}


void transistor_7 (int value) // Wather pump
{
    int pin = PIN_TRANSISTOR_7;
    int inaccuracy = 2;
    float (*sensor_function) () = readSoilMoisture;

    if ((float)value - sensor_function() > inaccuracy && value != 0)
    {
        digitalWrite(pin, HIGH);
    }
    else
    {
        digitalWrite(pin, LOW);
    }
}