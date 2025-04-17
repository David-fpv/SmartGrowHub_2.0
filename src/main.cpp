#include <Arduino.h>
// #include <WiFi.h>
// #include <PubSubClient.h>
#include "sensor_handler.h"
#include "setting_handler.h"
#include "module_functions.h"
#include "sensor_functions.h"
#include "json_handler.h"


// // Wi-Fi settings
// const char* ssid = "David phone 2a";
// const char* password = "qwerty555";

// // MQTT settings
// const char* mqttServer = "broker.emqx.io";
// const int mqttPort = 1883;
// const char* mqttUser = "";  // Укажите, если требуется
// const char* mqttPassword = "";  // Укажите, если требуется

// Objects
// WiFiClient espClient;
// PubSubClient client(espClient);
SettingHandler modules;
SensorHandler info;
JsonHandler json_handler;


// void callback(char* topic, byte payload[], unsigned int length)
// {
//     Serial.print("Topic: ");
//     Serial.println(topic);
  
//     Serial.print("Message: ");
//     for (int i = 0; i < length; i++) {
//       Serial.print((char)payload[i]);
//     }
//     Serial.println();
// };


// void setupWiFiMQTT()
// {
//     // Подключение к Wi-Fi
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.println("Connecting to Wi-Fi...");
//     }
//     Serial.println("Wi-Fi conncted!");

//     // Подключение к MQTT
//     client.setServer(mqttServer, mqttPort);
//     client.setCallback(callback); // Установка функции обратного вызова
//     client.setBufferSize(1000);

//     while (!client.connected()) {
//         Serial.println("Connecting to MQTT...");
//         if (client.connect("ESP32_Client", mqttUser, mqttPassword)) {
//         Serial.println("MQtt connected!");
//         client.subscribe("/Gomel/Tar/12042225/");  // Подписка на топик
//         Serial.println("The subscription was completed successfully");
//         } else {
//         Serial.print("Error connect: ");
//         Serial.print(client.state());
//         delay(2000);
//         }
//     }
// };

const char* json_dayLightComponent = R"({
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
                "start": "01T00:00",
                "end": "02T23:10"
            }
        }
    ]
})";


const char* json_uvLightComponent = R"({
    "type": "uvLightComponent",
    "version_id": "01JKY5E122HBQSZKXMF0F7HR44",
    "mode": 3,
    "entries": [
        {
            "quantity": {
                "magnitude": 15,
                "unit": 1
            },
            "interval": {
                "start": "01T21:00",
                "end": "01T00:49"
            }
        }
    ]
})";

const char* json_heaterComponent = R"({
    "type": "heaterComponent",
    "version_id": "01JKY5E122HBQSZKXMF0F7HR44",
    "mode": 3,
    "entries": [
        {
            "quantity": {
                "magnitude": 40,
                "unit": 1
            },
            "interval": {
                "start": "01T00:10",
                "end": "01T00:40"
            }
        }
    ]
})";

const char* json_humidifierComponent = R"({
    "type": "humidifierComponent",
    "version_id": "01JKY5E122HBQSZKXMF0F7HR44",
    "mode": 3,
    "entries": [
        {
            "quantity": {
                "magnitude": 15,
                "unit": 1
            },
            "interval": {
                "start": "01T00:01",
                "end": "01T00:18"
            }
        }
    ]
})";

const char* json_fanComponent = R"({
    "type": "fanComponent",
    "version_id": "01JKY5E122HBQSZKXMF0F7HR44",
    "mode": 0,
    "entries": [
        {
            "quantity": {
                "magnitude": 15,
                "unit": 1
            },
            "interval": {
                "start": "01T00:00",
                "end": "01T23:59"
            }
        }
    ]
})";


void setup() {
    delay(2000);
    Serial.begin(9600);
    delay(500);
    initialization_sensors();
    delay(500);
    initialization_module();
    delay(500);

    modules.AddSetting(Setting("dayLightComponent", blink, json_handler.parseProgram(json_dayLightComponent, sizeof(json_dayLightComponent))));
    // modules.AddSetting(Setting(std::string("uvLightComponent"), transistor_2, json_handler.parseProgram(std::string(json_uvLightComponent))));
    // modules.AddSetting(Setting(std::string("heaterComponent"), transistor_3, json_handler.parseProgram(std::string(json_heaterComponent))));
    // modules.AddSetting(Setting(std::string("humidifierComponent"), transistor_4, json_handler.parseProgram(std::string(json_humidifierComponent))));
    // modules.AddSetting(Setting(std::string("fanComponent"), transistor_5, json_handler.parseProgram(std::string(json_fanComponent))));

    // info.addSensorInfo(SensorInfo(1, "airTemperature", "C", readTemperatureBME));
    // info.addSensorInfo(SensorInfo(2, "airHumidity", "%", readHumidityBME));
    // info.addSensorInfo(SensorInfo(3, "pressure", "Pa", readPressureBME));
    // info.addSensorInfo(SensorInfo(4, "plantHeight", "cm", readDistance));
    // info.addSensorInfo(SensorInfo(5, "light", "%", readLight));
    // info.addSensorInfo(SensorInfo(6, "soilTemperature", "C", readSoilTemperature));
    // info.addSensorInfo(SensorInfo(7, "soilMoisture", "%", readSoilMoisture));
}


TimeStamp time_now;
void loop() {
    //client.loop();
    modules.CurateAllSetting();
    // time_now = getTimeStamp();
    // Serial.println("Time now: ");
    // Serial.println(static_cast<int>(time_now.day_));
    // Serial.println(time_now.hour_);
    // Serial.println(time_now.minutes_);
    delay(100);

    //printTime();
    // Serial.println(json_handler.getJsonSensorsData(info.getAllReadings()));    
}
