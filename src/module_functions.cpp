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


void blink(Setting setting, TimeStamp time_now)
{
    int pin = PIN_LED;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        digitalWrite(pin, 1);
    
    case SettingMode::Auto:
        digitalWrite(pin, 1);
        delay(200);
        digitalWrite(pin, 0);
        delay(200);

    case SettingMode::Off:
    default:
        digitalWrite(pin, 0);
    }
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


void servo (Setting setting, TimeStamp time_now) // AirFlap
{
    servo_on_off(0);
    // switch (static_cast<int>(program.GetMode()))
    // {        
    //     case static_cast<int>(SettingMode::On):
    //         servo_on_off(1);
    //         break;
        
    //     case static_cast<int>(SettingMode::Daily):
    //         for (int i = 0; i < program.GetEntries().size(); i++)
    //         {
    //             Entry entry = program.GetEntries()[i];
    //             if (inHourAndMinute(entry.GetTimeInterval(), time_now))
    //             {
    //                 if (entry.GetQuantity().unit_ == Unit::Percent)
    //                 {
    //                     if (entry.GetQuantity().magnitude_ > 0)
    //                     {                   
    //                         servo_on_off(1);
    //                     } else 
    //                     {
    //                         servo_on_off(0);
    //                     }
    //                 }
    //                 return;
    //             }
    //         }
    //         servo_on_off(0);
    //         break;
        
    //     case static_cast<int>(SettingMode::Off):
    //     default:    
    //         servo_on_off(0);
    //         break;
    // }
}


void dayLight (Setting setting, TimeStamp time_now) // Daylight
{
    int pin = PIN_TRANSISTOR_1;

    switch (static_cast<int>(setting.GetMode()))
    {
    case 1:
        analogWrite(pin, 255);
        break;

    case 2:
        for (const auto& unit: setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Prefer)
                {
                    analogWrite(pin, 255); // Edit
                }
                else if (unit.GetUnitKind() == UnitKind::Power)
                {
                    analogWrite(pin, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55));
                }
                return;
            }
        }

        analogWrite(pin, 0);
        break;

    case 0:
    default:
        analogWrite(pin, 0);
        break;
    }

    // switch (static_cast<int>(program.GetMode()))
    // {        
    //     case static_cast<int>(SettingMode::On):
    //         digitalWrite(pin, HIGH);
    //         break;
        
    //     case static_cast<int>(SettingMode::Daily):
    //         for (int i = 0; i < program.GetEntries().size(); i++)
    //         {
    //             Entry entry = program.GetEntries()[i];
    //             if (inHourAndMinute(entry.GetTimeInterval(), time_now))
    //             {
    //                 if (entry.GetQuantity().unit_ == Unit::Percent)
    //                 {
    //                     if (entry.GetQuantity().magnitude_ > 0)
    //                     {                   
    //                         digitalWrite(pin, HIGH);
    //                     } else 
    //                     {
    //                         digitalWrite(pin, LOW);
    //                     }
    //                 }
    //                 return;
    //             }
    //         }
    //         digitalWrite(pin, LOW);
    //         break;
        
    //     case static_cast<int>(SettingMode::Off):
    //     default:    
    //         digitalWrite(pin, LOW);
    //         break;
    // }
}


void phytoLight (Setting setting, TimeStamp time_now) // Phyto lighting
{
    int pin = PIN_TRANSISTOR_2;
    digitalWrite(pin, LOW);

    // switch (static_cast<int>(program.GetMode()))
    // {        
    //     case static_cast<int>(SettingMode::On):
    //         digitalWrite(pin, HIGH);
    //         break;
        
    //     case static_cast<int>(SettingMode::Daily):
    //         for (int i = 0; i < program.GetEntries().size(); i++)
    //         {
    //             Entry entry = program.GetEntries()[i];
    //             if (inHourAndMinute(entry.GetTimeInterval(), time_now))
    //             {
    //                 if (entry.GetQuantity().unit_ == Unit::Percent)
    //                 {
    //                     if (entry.GetQuantity().magnitude_ > 0)
    //                     {                   
    //                         digitalWrite(pin, HIGH);
    //                     } else 
    //                     {
    //                         digitalWrite(pin, LOW);
    //                     }
    //                 }
    //                 return;
    //             }
    //         }
    //         digitalWrite(pin, LOW);
    //         break;
        
    //     case static_cast<int>(SettingMode::Off):
    //     default:    
    //         digitalWrite(pin, LOW);
    //         break;
    // }
}


void heater (Setting setting, TimeStamp time_now) // Heater
{
    int pin = PIN_TRANSISTOR_3;
    digitalWrite(pin, LOW);
    // int inaccuracy = 2;
    // float (*sensor_function) () = readTemperatureBME;

    // switch (static_cast<int>(program.GetMode()))
    // {        
    //     case static_cast<int>(SettingMode::On):
    //         digitalWrite(pin, HIGH);
    //         break;
        
    //     case static_cast<int>(SettingMode::Daily):
    //         for (int i = 0; i < program.GetEntries().size(); i++)
    //         {
    //             Entry entry = program.GetEntries()[i];
    //             if (inHourAndMinute(entry.GetTimeInterval(), time_now))
    //             {
    //                 if (entry.GetQuantity().unit_ == Unit::Percent)
    //                 {
    //                     if (entry.GetQuantity().magnitude_ > 0)
    //                     {                   
    //                         digitalWrite(pin, HIGH);
    //                     } else 
    //                     {
    //                         digitalWrite(pin, LOW);
    //                     }
    //                 }
    //                 else if (entry.GetQuantity().unit_ == Unit::Quantity)
    //                 {
    //                     int sensor_data = sensor_function();
    //                     Serial.print("Temperature: ");
    //                     Serial.println(sensor_data);
    //                     if (entry.GetQuantity().magnitude_ - sensor_data > inaccuracy)
    //                     {                   
    //                         digitalWrite(pin, HIGH);
    //                     } else 
    //                     {
    //                         digitalWrite(pin, LOW);
    //                     }
    //                 }
    //                 return;
    //             }
    //         }
    //         digitalWrite(pin, LOW);
    //         break;
        
    //     case static_cast<int>(SettingMode::Off):
    //     default:    
    //         digitalWrite(pin, LOW);
    //         break;
    // }
}


void airHumidifier (Setting setting, TimeStamp time_now) // Air humidifier
{
    int pin = PIN_TRANSISTOR_4;
    digitalWrite(pin, LOW);
    // int inaccuracy = 2;
    // float (*sensor_function) () = readHumidityBME;

    // switch (static_cast<int>(program.GetMode()))
    // {        
    //     case static_cast<int>(SettingMode::On):
    //         digitalWrite(pin, HIGH);
    //         break;
        
    //     case static_cast<int>(SettingMode::Daily):
    //         for (int i = 0; i < program.GetEntries().size(); i++)
    //         {
    //             Entry entry = program.GetEntries()[i];
    //             if (inHourAndMinute(entry.GetTimeInterval(), time_now))
    //             {
    //                 if (entry.GetQuantity().unit_ == Unit::Percent)
    //                 {
    //                     if (entry.GetQuantity().magnitude_ - sensor_function() > inaccuracy)
    //                     {                   
    //                         digitalWrite(pin, HIGH);
    //                     } else
    //                     {
    //                         digitalWrite(pin, LOW);
    //                     }
    //                 }
    //                 return;
    //             }
    //         }
    //         digitalWrite(pin, LOW);
    //         break;
        
    //     case static_cast<int>(SettingMode::Off):
    //     default:    
    //         digitalWrite(pin, LOW);
    //         break;
    // }
}


void fan (Setting setting, TimeStamp time_now) // Fan
{
    int pin = PIN_TRANSISTOR_5;
    digitalWrite(pin, LOW);

    // switch (static_cast<int>(program.GetMode()))
    // {        
    //     case static_cast<int>(SettingMode::On):
    //         digitalWrite(pin, HIGH);
    //         break;
        
    //     case static_cast<int>(SettingMode::Daily):
    //         for (int i = 0; i < program.GetEntries().size(); i++)
    //         {
    //             Entry entry = program.GetEntries()[i];
    //             if (inHourAndMinute(entry.GetTimeInterval(), time_now))
    //             {
    //                 if (entry.GetQuantity().unit_ == Unit::Percent)
    //                 {
    //                     if (entry.GetQuantity().magnitude_ > 0)
    //                     {                   
    //                         digitalWrite(pin, HIGH);
    //                     } else 
    //                     {
    //                         digitalWrite(pin, LOW);
    //                     }
    //                 }
    //                 return;
    //             }
    //         }
    //         digitalWrite(pin, LOW);
    //         break;
        
    //     case static_cast<int>(SettingMode::Off):
    //     default:    
    //         digitalWrite(pin, LOW);
    //         break;
    // }
}


void waterPump (Setting setting, TimeStamp time_now) // Wather pump
{
    int pin = PIN_TRANSISTOR_7;
    digitalWrite(pin, LOW);
    // int inaccuracy = 2;
    // float (*sensor_function) () = readSoilMoisture;

    // switch (static_cast<int>(program.GetMode()))
    // {        
    //     case static_cast<int>(SettingMode::On):
    //         digitalWrite(pin, HIGH);
    //         break;
        
    //     case static_cast<int>(SettingMode::Daily):
    //         for (int i = 0; i < program.GetEntries().size(); i++)
    //         {
    //             Entry entry = program.GetEntries()[i];
    //             if (inHourAndMinute(entry.GetTimeInterval(), time_now))
    //             {
    //                 if (entry.GetQuantity().unit_ == Unit::Percent)
    //                 {
    //                     if (entry.GetQuantity().magnitude_ - sensor_function() > inaccuracy)
    //                     {                   
    //                         digitalWrite(pin, HIGH);
    //                     } else 
    //                     {
    //                         digitalWrite(pin, LOW);
    //                     }
    //                 }
    //                 return;
    //             }
    //         }
    //         digitalWrite(pin, LOW);
    //         break;
        
    //     case static_cast<int>(SettingMode::Off):
    //     default:    
    //         digitalWrite(pin, LOW);
    //         break;
    // }
}