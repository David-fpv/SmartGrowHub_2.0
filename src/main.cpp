#include <Arduino.h>
#include "setting.h"
#include "sensor_handler.h"

//#define THRESHOLD 300
#define THRESHOLD 263

Setting smart_grow_hub();
SensorHandler info;

void readAllSensors();

void setup() {
    Serial.begin(9600);
    initialization();
    info.addSensorData(1, "Illumination", "%");
    info.addSensorData(2, "Height", "cm");

}
   
void loop() {
    readAllSensors();
    Serial.println(info.getStringJson());
    delay(1000);
}

void readAllSensors()
{
    info.setValue(1, "Illumination", (double)readIllumination());
    info.setValue(2, "Height", (double)readHeight());
}

