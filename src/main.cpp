#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "wifi_mqtt_functions.hpp"
#include "sensor_handler.h"
#include "setting_handler.h"
#include "setting_mode.h"
#include "module_functions.h"
#include "sensor_functions.h"
#include "json_handler.h"

const char device_id[] = "A0001";

const float CONTAINER_DEPTH_CM = 35.0f;

// Backing buffers for string fields in Config
static char cfg_ssid[33];
static char cfg_password[65];
static char cfg_server[65];
static char cfg_user[33];
static char cfg_mqtt_pass[65];
static char cfg_topic_sensors[65];
static char cfg_topic_modules[65];
static char cfg_topic_response[65];

static WifiMqttManager::Config mqtt_config = {
    cfg_ssid, cfg_password, cfg_server, 1883,
    cfg_user, cfg_mqtt_pass,
    cfg_topic_sensors, cfg_topic_modules, cfg_topic_response,
    20, 10, 1000, 10800
};

static void loadConfig() {
    // Defaults
    strncpy(cfg_ssid,           "DAVID-laptop",         sizeof(cfg_ssid) - 1);
    strncpy(cfg_password,       "qwerty555",            sizeof(cfg_password) - 1);
    strncpy(cfg_server,         "broker.emqx.io",       sizeof(cfg_server) - 1);
    strncpy(cfg_user,           "",                     sizeof(cfg_user) - 1);
    strncpy(cfg_mqtt_pass,      "",                     sizeof(cfg_mqtt_pass) - 1);
    strncpy(cfg_topic_sensors,  "/Gomel/Tar/sensors/",  sizeof(cfg_topic_sensors) - 1);
    strncpy(cfg_topic_modules,  "/Gomel/Tar/modules/",  sizeof(cfg_topic_modules) - 1);
    strncpy(cfg_topic_response, "/Gomel/Tar/response/", sizeof(cfg_topic_response) - 1);
    mqtt_config.port              = 1883;
    mqtt_config.max_wifi_attempts = 20;
    mqtt_config.max_mqtt_attempts = 10;
    mqtt_config.mqtt_buffer_size  = 1000;
    mqtt_config.utc_offset_sec    = 10800;

    if (!LittleFS.exists("/config.json")) {
        Serial.println("loadConfig: /config.json not found, using defaults");
        return;
    }

    File f = LittleFS.open("/config.json", "r");
    if (!f) { Serial.println("loadConfig: open failed"); return; }

    StaticJsonDocument<512> doc;
    DeserializationError err = deserializeJson(doc, f);
    f.close();

    if (err) {
        Serial.printf("loadConfig: parse error: %s, using defaults\n", err.c_str());
        return;
    }

    if (doc["ssid"])           strncpy(cfg_ssid,           doc["ssid"],           sizeof(cfg_ssid) - 1);
    if (doc["password"])       strncpy(cfg_password,       doc["password"],       sizeof(cfg_password) - 1);
    if (doc["server"])         strncpy(cfg_server,         doc["server"],         sizeof(cfg_server) - 1);
    if (doc["user"])           strncpy(cfg_user,           doc["user"],           sizeof(cfg_user) - 1);
    if (doc["mqtt_pass"])      strncpy(cfg_mqtt_pass,      doc["mqtt_pass"],      sizeof(cfg_mqtt_pass) - 1);
    if (doc["topic_sensors"])  strncpy(cfg_topic_sensors,  doc["topic_sensors"],  sizeof(cfg_topic_sensors) - 1);
    if (doc["topic_modules"])  strncpy(cfg_topic_modules,  doc["topic_modules"],  sizeof(cfg_topic_modules) - 1);
    if (doc["topic_response"]) strncpy(cfg_topic_response, doc["topic_response"], sizeof(cfg_topic_response) - 1);

    if (doc["port"])              mqtt_config.port              = doc["port"];
    if (doc["max_wifi_attempts"]) mqtt_config.max_wifi_attempts = doc["max_wifi_attempts"];
    if (doc["max_mqtt_attempts"]) mqtt_config.max_mqtt_attempts = doc["max_mqtt_attempts"];
    if (doc["mqtt_buffer_size"])  mqtt_config.mqtt_buffer_size  = doc["mqtt_buffer_size"];
    if (doc["utc_offset_sec"])    mqtt_config.utc_offset_sec    = doc["utc_offset_sec"];

    Serial.println("loadConfig: loaded from /config.json");
}


// Objects
SettingHandler modules;
SensorHandler  info;
JsonHandler    json_handler;


static void printFiles() {
    File root = LittleFS.open("/");
    if (!root) { Serial.println("printFiles: can't open root"); return; }
    File f = root.openNextFile();
    while (f) {
        Serial.printf("=== %s (%d bytes) ===\n", f.name(), (int)f.size());
        while (f.available())
            Serial.write(f.read());
        Serial.println();
        f.close();
        f = root.openNextFile();
    }
    root.close();
}


void setup() {
    delay(2500);
    Serial.begin(9600);

    if (!LittleFS.begin(true))
        Serial.println("LittleFS: mount failed");

    loadConfig();

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
    if (Serial.available() && Serial.read() == 'd')
        printFiles();

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
