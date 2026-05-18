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
    switch (setting.GetMode())
    {
    case SettingMode::On:
        analogWrite(PIN_LED, 255);
        break;

    case SettingMode::Auto:
    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                    analogWrite(PIN_LED, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55f));
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                {
                    analogWrite(PIN_LED, 255);
                    delay(200);
                    analogWrite(PIN_LED, 0);
                    delay(200);
                }
                return;
            }
        }
        analogWrite(PIN_LED, 0);
        break;

    case SettingMode::Off:
    default:
        analogWrite(PIN_LED, 0);
        break;
    }
}


static int servo_angle = 80;

static void servo_set_angle(int target)
{
    target = constrain(target, 20, 80);
    while (servo_angle < target) { myservo.write(++servo_angle); delay(10); }
    while (servo_angle > target) { myservo.write(--servo_angle); delay(10); }
}

static void servo_set_percent(int percent)
{
    servo_set_angle(map(constrain(percent, 0, 100), 0, 100, 80, 20));
}


void servo(Setting setting, TimeStamp time_now)
{
    const float inaccuracy = 1.0f;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        servo_set_percent(100);
        break;

    case SettingMode::Auto:
    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                    servo_set_percent(unit.GetQuantity().magnitude_);
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                {
                    float target = unit.GetQuantity().magnitude_;
                    servo_set_percent((readTemperatureBME() - target) > inaccuracy ? 100 : 0);
                }
                return;
            }
        }
        servo_set_percent(0);
        break;

    case SettingMode::Off:
    default:
        servo_set_percent(0);
        break;
    }
}


void dayLight(Setting setting, TimeStamp time_now)
{
    const int pin = PIN_TRANSISTOR_1;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        analogWrite(pin, 255);
        break;

    case SettingMode::Auto:
    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                    analogWrite(pin, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55f));
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                    analogWrite(pin, 255);
                return;
            }
        }
        analogWrite(pin, 0);
        break;

    case SettingMode::Off:
    default:
        analogWrite(pin, 0);
        break;
    }
}


void phytoLight(Setting setting, TimeStamp time_now)
{
    const int pin = PIN_TRANSISTOR_2;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        analogWrite(pin, 255);
        break;

    case SettingMode::Auto:
    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                    analogWrite(pin, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55f));
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                    analogWrite(pin, 255);
                return;
            }
        }
        analogWrite(pin, 0);
        break;

    case SettingMode::Off:
    default:
        analogWrite(pin, 0);
        break;
    }
}


void heater(Setting setting, TimeStamp time_now)
{
    const int   pin        = PIN_TRANSISTOR_3;
    const float inaccuracy = 1.0f;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        analogWrite(pin, 255);
        break;

    case SettingMode::Auto:
    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                {
                    analogWrite(pin, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55f));
                }
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                {
                    float target = unit.GetQuantity().magnitude_;
                    analogWrite(pin, (target - readTemperatureBME()) > inaccuracy ? 255 : 0);
                }
                return;
            }
        }
        analogWrite(pin, 0);
        break;

    case SettingMode::Off:
    default:
        analogWrite(pin, 0);
        break;
    }
}


void airHumidifier(Setting setting, TimeStamp time_now)
{
    const int   pin        = PIN_TRANSISTOR_7;
    const float inaccuracy = 3.0f;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        analogWrite(pin, 255);
        break;

    case SettingMode::Auto:
    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                {
                    analogWrite(pin, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55f));
                }
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                {
                    float target = unit.GetQuantity().magnitude_;
                    analogWrite(pin, (target - readHumidityBME()) > inaccuracy ? 255 : 0);
                }
                return;
            }
        }
        analogWrite(pin, 0);
        break;

    case SettingMode::Off:
    default:
        analogWrite(pin, 0);
        break;
    }
}


void fan(Setting setting, TimeStamp time_now)
{
    const int pin = PIN_TRANSISTOR_5;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        analogWrite(pin, 255);
        break;

    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                    analogWrite(pin, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55f));
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                    analogWrite(pin, 0);
                return;
            }
        }
        analogWrite(pin, 0);
        break;

    case SettingMode::Off:
    default:
        analogWrite(pin, 0);
        break;
    }
}


void waterPump(Setting setting, TimeStamp time_now)
{
    const int   pin        = PIN_TRANSISTOR_6;
    const float inaccuracy = 5.0f;

    switch (setting.GetMode())
    {
    case SettingMode::On:
        analogWrite(pin, 255);
        break;

    case SettingMode::Auto:
    case SettingMode::Daily:
        for (const auto& unit : setting.GetSchedule().GetScheduleUnits())
        {
            if (inTimeRange(unit.GetTimeInterval(), time_now))
            {
                if (unit.GetUnitKind() == UnitKind::Power)
                {
                    analogWrite(pin, static_cast<int>(unit.GetQuantity().magnitude_ * 2.55f));
                }
                else if (unit.GetUnitKind() == UnitKind::Prefer)
                {
                    float target = unit.GetQuantity().magnitude_;
                    int max_time = 5000; // 5 second 
                    while ((target - readSoilMoisture()) > inaccuracy && max_time > 0)
                    {
                        analogWrite(pin, 255);
                        max_time -= 10;
                        delay(10);
                    }
                    analogWrite(pin, 0);
                }
                return;
            }
        }
        analogWrite(pin, 0);
        break;

    case SettingMode::Off:
    default:
        analogWrite(pin, 0);
        break;
    }
}
