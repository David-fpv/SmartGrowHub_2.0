#include <Arduino.h>
#include <LittleFS.h>
#include "wifi_mqtt_functions.hpp"
#include "sensor_handler.h"
#include "setting_handler.h"
#include "setting_mode.h"
#include "module_functions.h"
#include "sensor_functions.h"
#include "json_handler.h"

const char device_id[] = "A0001";

const float CONTAINER_DEPTH_CM = 35.0f;

const WifiMqttManager::Config mqtt_config = {
    /* ssid             */ "DAVID-laptop",
    /* password         */ "qwerty555",
    /* server           */ "broker.emqx.io",
    /* port             */ 1883,
    /* user             */ "",
    /* mqtt_pass        */ "",
    /* topic_sensors    */ "/Gomel/Tar/sensors/",
    /* topic_modules    */ "/Gomel/Tar/modules/",
    /* topic_response   */ "/Gomel/Tar/response/",
    /* max_wifi_attempts*/ 20,
    /* max_mqtt_attempts*/ 10,
    /* mqtt_buffer_size */ 1000,
    /* utc_offset_sec  */ 10800, // UTC+3
};

// Objects
SettingHandler modules;
SensorHandler info;
JsonHandler json_handler;


void setup() {
    delay(2500);
    Serial.begin(9600);

    if (!LittleFS.begin(true))
        Serial.println("LittleFS: mount failed");

    initialization_sensors();
    setContainerDepth(CONTAINER_DEPTH_CM);
    initialization_module();
    delay(100);
    WifiMqttManager::instance().init(&modules, &json_handler, device_id, mqtt_config);
    WifiMqttManager::instance().setup();
    delay(100);

    modules.AddSetting( Setting(ModuleType::Led,        SettingMode::Off,   blink,          4));
    modules.AddSetting( Setting(ModuleType::DayLight,   SettingMode::Off,   dayLight,      12));
    modules.AddSetting( Setting(ModuleType::UvLight,    SettingMode::Off,   phytoLight,    12));
    modules.AddSetting( Setting(ModuleType::Heater,     SettingMode::Off,   heater,        10));
    modules.AddSetting( Setting(ModuleType::Humidifier, SettingMode::Off,   airHumidifier, 10));
    modules.AddSetting( Setting(ModuleType::Fan,        SettingMode::Off,   fan,            4));
    modules.AddSetting( Setting(ModuleType::WaterPump,  SettingMode::Off,   waterPump,      4));
    modules.AddSetting( Setting(ModuleType::AirFlap,    SettingMode::Off,   servo,         10));


    modules.load();

    info.addSensorInfo( SensorInfo(  1,  "airTemperature",   "C",    readTemperatureBME));
    info.addSensorInfo( SensorInfo(  2,  "airHumidity",      "%",    readHumidityBME));
    info.addSensorInfo( SensorInfo(  3,  "pressure",         "Pa",   readPressureBME));
    info.addSensorInfo( SensorInfo(  4,  "plantHeight",      "cm",   readPlantHeight));
    info.addSensorInfo( SensorInfo(  5,  "light",            "%",    readLight));
    info.addSensorInfo( SensorInfo(  6,  "soilTemperature",  "C",    readSoilTemperature));
    info.addSensorInfo( SensorInfo(  7,  "soilMoisture",     "%",    readSoilMoisture));
}


long long previousTime_1 = millis();
long long previousTime_2 = millis();
void loop() {
    WifiMqttManager::instance().loop();

    if (previousTime_1 + 100 < millis())
    {
        previousTime_1 = millis();
        modules.CurateAllSetting();
    }

    if (previousTime_2 + 30000 < millis())
    {
        previousTime_2 = millis();

        const char* message = json_handler.getJsonSensorsData(info, device_id);
        Serial.println(message);
        WifiMqttManager::instance().publish(mqtt_config.topic_sensors, message);
        printTime();
    }
}
