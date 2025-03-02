#include <Arduino.h>
#include "sensor_handler.h"
#include "setting_handler.h"
#include "module_functions.h"
#include "json_handler.h"


const char* json = R"({
    "type": "dayLightComponent",
    "version_id": "01JKY5E122HBQSZKXMF0F7HR44",
    "mode": 1,
    "entries": [
        {
            "quantity": {
                "magnitude": 15,
                "unit": 1
            },
            "interval": {
                "start": "01T08:00",
                "end": "02T08:00"
            }
        },
        {
            "quantity": {
                "magnitude": 26,
                "unit": "°C"
            },
            "interval": {
                "start": "02T12:00",
                "end": "02T23:00"
            }
        },
        {
            "quantity": {
                "magnitude": 10,
                "unit": "%"
            },
            "interval": {
                "start": "04T12:00",
                "end": "04T15:00"
            }
        }
    ]
})";


SettingHandler modules;
SensorHandler info;
JsonHandler json_handler;


void setup() {
    Serial.begin(115200);
    modules.AddSetting(Setting(std::string("dayLightComponent"), blink, json_handler.parseProgram(std::string(json))));
}


void loop() {
    modules.CurateSetting(std::string("dayLightComponent"));
}
