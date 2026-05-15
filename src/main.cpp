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
    injectMqttDependencies(&modules, &json_handler, device_id);
    setupWiFiMQTT();
    delay(100);

    modules.AddSetting( Setting(std::string("led"),         SettingMode::Off,   blink));
    modules.AddSetting( Setting(std::string("dayLight"),    SettingMode::Off,   dayLight));
    modules.AddSetting( Setting(std::string("uvLight"),     SettingMode::Off,   phytoLight));
    modules.AddSetting( Setting(std::string("heater"),      SettingMode::Off,   heater));
    modules.AddSetting( Setting(std::string("humidifier"),  SettingMode::Off,   airHumidifier));
    modules.AddSetting( Setting(std::string("fan"),         SettingMode::Off,   fan));
    modules.AddSetting( Setting(std::string("waterPump"),   SettingMode::Off,   waterPump));
    modules.AddSetting( Setting(std::string("airFlap"),     SettingMode::Off,   servo));


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
    wifi_mqtt_loop();

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
        mqttPublishInfo(json_handler.getJsonSensorsData(info.getAllReadings()));
        printTime();
    }    
}
