#include <Arduino.h>
#include "wifi_mqtt_functions.hpp"
#include <string>
#include "sensor_handler.h"
#include "setting_handler.h"
#include "setting_mode.h"
#include "module_functions.h"
#include "sensor_functions.h"
#include "json_handler.h"

std::string device_id = "A0001";

const WifiMqttManager::Config mqtt_config = {
    /* ssid             */ "DAVID-laptop",
    /* password         */ "qwerty555",
    /* server           */ "broker.emqx.io",
    /* port             */ 1883,
    /* user             */ "",
    /* mqtt_pass        */ "",
    /* topic_sensors    */ "/Gomel/Tar/sensors/",
    /* topic_modules    */ "/Gomel/Tar/modules/",
    /* max_wifi_attempts*/ 20,
    /* max_mqtt_attempts*/ 10,
    /* mqtt_buffer_size */ 1000,
    /* utc_offset_sec  */ 10800, // UTC+3
};

// Objects
SettingHandler modules;
SensorHandler info;
JsonHandler json_handler;


// const char* json_dayLightComponent = R"({
//     "type": "dayLight",
//     "version_id": "01JKY5E122HBQSZKXMF0F7HR44",
//     "mode": 3,
//     "entries": [
//         {
//             "quantity": {
//                 "magnitude": 15,
//                 "unit": 1
//             },
//             "interval": {
//                 "start": "01T00:00",
//                 "end": "02T23:10"
//             }
//         }
//     ]
// })";


// const char* json_default = R"({
//     "type": "default",
//     "version_id": "01JKY5E122HBQSZKXMF0F7HR44",
//     "mode": 0,
//     "entries": []
// })";


void setup() {
    delay(2500);
    Serial.begin(9600);
    initialization_sensors();
    initialization_module();
    delay(100);
    WifiMqttManager::instance().init(&modules, &json_handler, device_id, mqtt_config);
    WifiMqttManager::instance().setup();
    delay(100);

    modules.AddSetting( Setting(ModuleType::Led,        SettingMode::Off,   blink));
    modules.AddSetting( Setting(ModuleType::DayLight,   SettingMode::Off,   dayLight));
    modules.AddSetting( Setting(ModuleType::UvLight,    SettingMode::Off,   phytoLight));
    modules.AddSetting( Setting(ModuleType::Heater,     SettingMode::Off,   heater));
    modules.AddSetting( Setting(ModuleType::Humidifier, SettingMode::Off,   airHumidifier));
    modules.AddSetting( Setting(ModuleType::Fan,        SettingMode::Off,   fan));
    modules.AddSetting( Setting(ModuleType::WaterPump,  SettingMode::Off,   waterPump));
    modules.AddSetting( Setting(ModuleType::AirFlap,    SettingMode::Off,   servo));


    info.addSensorInfo( SensorInfo(  1,  "airTemperature",   "C",    readTemperatureBME));
    info.addSensorInfo( SensorInfo(  2,  "airHumidity",      "%",    readHumidityBME));
    info.addSensorInfo( SensorInfo(  3,  "pressure",         "Pa",   readPressureBME));
    info.addSensorInfo( SensorInfo(  4,  "plantHeight",      "cm",   readDistance));
    info.addSensorInfo( SensorInfo(  5,  "light",            "%",    readLight));
    info.addSensorInfo( SensorInfo(  6,  "soilTemperature",  "C",    readSoilTemperature));
    info.addSensorInfo( SensorInfo(  7,  "soilMoisture",     "%",    readSoilMoisture));
    //info.addSensorInfo(SensorInfo(8, "randomNumber", "-", readRandomNumber));
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
        
        std::string message = json_handler.getJsonSensorsData(info.getAllReadings());
        Serial.println(message.c_str());
        WifiMqttManager::instance().publishInfo(json_handler.getJsonSensorsData(info.getAllReadings()));
        printTime();
    }    
}
