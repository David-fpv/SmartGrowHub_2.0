#include <Arduino.h>
#include "sensor_handler.h"
#include "sensor_info.h"

//#define THRESHOLD 300
#define THRESHOLD 263

//Setting smart_grow_hub();
SensorHandler info;

void readAllSensors();

void setup() {

    Serial.begin(115200);
    //initialization();
    info.addSensorInfo(SensorInfo(1, "RandomNumber", "$", readRandomNumber));

}
   
void loop() {
    Serial.println(info.getStringJson());
    delay(1000);
}
