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


void blink(Program program, TimeStamp time_now)
{
    int pin = PIN_LED;

    switch (static_cast<int>(program.GetMode()))
    {        
        case static_cast<int>(SettingMode::On):
            digitalWrite(pin, HIGH);
            break;
        
        case static_cast<int>(SettingMode::Daily):
            for (int i = 0; i < program.GetEntries().size(); i++)
            {
                Entry entry = program.GetEntries()[i];
                if (isHourAndMinute(entry.GetTimeInterval(), time_now))
                {
                    if (entry.GetQuantity().unit_ == Unit::Percent)
                    {
                        if (entry.GetQuantity().magnitude_ > 0)
                        {                   
                            int time = millis() % 2000 / 1000;
                            digitalWrite(pin, static_cast<bool>(time));
                        } else 
                        {
                            digitalWrite(pin, LOW);
                        }
                    }
                    return;
                }
            }
            digitalWrite(pin, LOW);
            break;
        
        case static_cast<int>(SettingMode::Off):
        default:    
            digitalWrite(pin, LOW);
            break;
    }
}


void servo (Program program, TimeStamp time_now)
{
    // static int angle = 10;
    // if (mode > 0 && angle < 20)
    // {
    //     for (pos = 10; pos <= 90; pos += 1)
    //     {
    //         myservo.write(pos);
    //         delay(20); 
    //     }
    //     angle = 90;
    // }
    
    // if (mode == 0 && angle > 80)
    // {
    //     for (pos = 90; pos >= 10; pos -= 1)
    //     {
    //         myservo.write(pos);
    //         delay(20);
    //     }
    //     angle = 10;
    // }
}


void transistor_1 (Program program, TimeStamp time_now) // Daylight
{
    int pin = PIN_TRANSISTOR_1;

    switch (static_cast<int>(program.GetMode()))
    {        
        case static_cast<int>(SettingMode::On):
            digitalWrite(pin, HIGH);
            break;
        
        case static_cast<int>(SettingMode::Daily):
            for (int i = 0; i < program.GetEntries().size(); i++)
            {
                Entry entry = program.GetEntries()[i];
                if (isHourAndMinute(entry.GetTimeInterval(), time_now))
                {
                    if (entry.GetQuantity().unit_ == Unit::Percent)
                    {
                        if (entry.GetQuantity().magnitude_ > 0)
                        {                   
                            digitalWrite(pin, HIGH);
                        } else 
                        {
                            digitalWrite(pin, LOW);
                        }
                    }
                    return;
                }
            }
            break;
        
        case static_cast<int>(SettingMode::Off):
        default:    
            digitalWrite(pin, LOW);
            break;
    }
}


void transistor_2 (Program program, TimeStamp time_now) // Phyto lighting
{
    int pin = PIN_TRANSISTOR_2;

    switch (static_cast<int>(program.GetMode()))
    {        
        case static_cast<int>(SettingMode::On):
            digitalWrite(pin, HIGH);
            break;
        
        case static_cast<int>(SettingMode::Daily):
            for (int i = 0; i < program.GetEntries().size(); i++)
            {
                Entry entry = program.GetEntries()[i];
                if (isHourAndMinute(entry.GetTimeInterval(), time_now))
                {
                    if (entry.GetQuantity().unit_ == Unit::Percent)
                    {
                        if (entry.GetQuantity().magnitude_ > 0)
                        {                   
                            digitalWrite(pin, HIGH);
                        } else 
                        {
                            digitalWrite(pin, LOW);
                        }
                    }
                    return;
                }
            }
            break;
        
        case static_cast<int>(SettingMode::Off):
        default:    
            digitalWrite(pin, LOW);
            break;
    }
}


void transistor_3 (Program program, TimeStamp time_now) // Heater
{
    int pin = PIN_TRANSISTOR_3;
    int inaccuracy = 2;
    float (*sensor_function) () = readTemperatureBME;

    switch (static_cast<int>(program.GetMode()))
    {        
        case static_cast<int>(SettingMode::On):
            digitalWrite(pin, HIGH);
            break;
        
        case static_cast<int>(SettingMode::Daily):
            for (int i = 0; i < program.GetEntries().size(); i++)
            {
                Entry entry = program.GetEntries()[i];
                if (isHourAndMinute(entry.GetTimeInterval(), time_now))
                {
                    if (entry.GetQuantity().unit_ == Unit::Quantity)
                    {
                        if (entry.GetQuantity().magnitude_ - sensor_function() > inaccuracy)
                        {                   
                            digitalWrite(pin, HIGH);
                        } else 
                        {
                            digitalWrite(pin, LOW);
                        }
                    }
                    return;
                }
            }
            break;
        
        case static_cast<int>(SettingMode::Off):
        default:    
            digitalWrite(pin, LOW);
            break;
    }
}


void transistor_4 (Program program, TimeStamp time_now) // Air humidifier
{
    int pin = PIN_TRANSISTOR_4;
    int inaccuracy = 2;
    float (*sensor_function) () = readHumidityBME;

    switch (static_cast<int>(program.GetMode()))
    {        
        case static_cast<int>(SettingMode::On):
            digitalWrite(pin, HIGH);
            break;
        
        case static_cast<int>(SettingMode::Daily):
            for (int i = 0; i < program.GetEntries().size(); i++)
            {
                Entry entry = program.GetEntries()[i];
                if (isHourAndMinute(entry.GetTimeInterval(), time_now))
                {
                    if (entry.GetQuantity().unit_ == Unit::Percent)
                    {
                        if (entry.GetQuantity().magnitude_ - sensor_function() > inaccuracy)
                        {                   
                            digitalWrite(pin, HIGH);
                        } else
                        {
                            digitalWrite(pin, LOW);
                        }
                    }
                    return;
                }
            }
            break;
        
        case static_cast<int>(SettingMode::Off):
        default:    
            digitalWrite(pin, LOW);
            break;
    }
}


void transistor_5 (Program program, TimeStamp time_now) // Fan
{
    int pin = PIN_TRANSISTOR_5;

    switch (static_cast<int>(program.GetMode()))
    {        
        case static_cast<int>(SettingMode::On):
            digitalWrite(pin, HIGH);
            break;
        
        case static_cast<int>(SettingMode::Daily):
            for (int i = 0; i < program.GetEntries().size(); i++)
            {
                Entry entry = program.GetEntries()[i];
                if (isHourAndMinute(entry.GetTimeInterval(), time_now))
                {
                    if (entry.GetQuantity().unit_ == Unit::Percent)
                    {
                        if (entry.GetQuantity().magnitude_ > 0)
                        {                   
                            digitalWrite(pin, HIGH);
                        } else 
                        {
                            digitalWrite(pin, LOW);
                        }
                    }
                    return;
                }
            }
            break;
        
        case static_cast<int>(SettingMode::Off):
        default:    
            digitalWrite(pin, LOW);
            break;
    }
}


void transistor_6 (Program program, TimeStamp time_now) // Wather pump
{
    int pin = PIN_TRANSISTOR_6;
    int inaccuracy = 2;
    float (*sensor_function) () = readSoilMoisture;

    switch (static_cast<int>(program.GetMode()))
    {        
        case static_cast<int>(SettingMode::On):
            digitalWrite(pin, HIGH);
            break;
        
        case static_cast<int>(SettingMode::Daily):
            for (int i = 0; i < program.GetEntries().size(); i++)
            {
                Entry entry = program.GetEntries()[i];
                if (isHourAndMinute(entry.GetTimeInterval(), time_now))
                {
                    if (entry.GetQuantity().unit_ == Unit::Percent)
                    {
                        if (entry.GetQuantity().magnitude_ - sensor_function() > inaccuracy)
                        {                   
                            digitalWrite(pin, HIGH);
                        } else 
                        {
                            digitalWrite(pin, LOW);
                        }
                    }
                    return;
                }
            }
            break;
        
        case static_cast<int>(SettingMode::Off):
        default:    
            digitalWrite(pin, LOW);
            break;
    }
}