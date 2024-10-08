#include <Arduino.h>
#include "sensor_handler.h"
#include "sensor_info.h"

#include "setting_handler.h"
#include "module_functions.h"

//#define THRESHOLD 300
#define THRESHOLD 263

//Setting smart_grow_hub();
SettingHandler modules;
SensorHandler info;

void readAllSensors();

void setup() {

    Serial.begin(115200);
    //initialization_sensors();
    initialization_module();
    //info.addSensorInfo(SensorInfo(1, "RandomNumber", "$", readRandomNumber));
    
    std::string testJson = "[{\"Type\": \"Watering\",\"Components\": [{\"Type\": \"Mode\",\"Value\": 1}]}]";

    modules.AddSetting(Setting("Led", blink));
    modules.SetStringJson(testJson);
    //modules.AddComponentToSetting("Led", Component("Mode", 1, ""));

}
   
void loop() {
    //Serial.println(info.getStringJson());
    modules.CurateAllSetting();
    delay(100);
}
