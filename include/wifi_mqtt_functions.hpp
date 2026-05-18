#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>
#include "setting_handler.h"
#include "json_handler.h"

void syncTimeFromNTP(int utcOffsetSec);

class WifiMqttManager {
public:
    struct Config {
        const char* ssid;
        const char* password;
        const char* server;
        int         port;
        const char* user;
        const char* mqtt_pass;
        const char* topic_sensors;
        const char* topic_modules;
        const char* topic_response;
        int         max_wifi_attempts;
        int         max_mqtt_attempts;
        int         mqtt_buffer_size;
        int         utc_offset_sec;
    };

    static WifiMqttManager& instance() {
        static WifiMqttManager inst;
        return inst;
    }

    WifiMqttManager(const WifiMqttManager&) = delete;
    WifiMqttManager& operator=(const WifiMqttManager&) = delete;

    void init(SettingHandler* modules, JsonHandler* json_handler,
              const char* device_id, const Config& config) {
        modules_      = modules;
        json_handler_ = json_handler;
        strncpy(device_id_, device_id, sizeof(device_id_) - 1);
        device_id_[sizeof(device_id_) - 1] = '\0';
        config_ = config;
    }

    void setup() {
        client_.setServer(config_.server, config_.port);
        client_.setCallback(mqttCallback);
        client_.setBufferSize(config_.mqtt_buffer_size);

        WiFi.setAutoReconnect(true);
        WiFi.persistent(false);

        connectToWiFi();
        connectToMQTT();
    }

    void loop() {
        if (client_.connected()) {
            client_.loop();
            return;
        }

        unsigned long now = millis();
        if (now - last_reconnect_ms_ < RECONNECT_INTERVAL_MS) return;
        last_reconnect_ms_ = now;

        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("loop: waiting for WiFi...");
            return;
        }
        connectToMQTT();
    }

    bool publish(const char* topic, const char* message) {
        if (!client_.connected()) return false;
        return client_.publish(topic, message);
    }

    void handleMessage(const char* topic, byte* payload, unsigned int length) {
        Serial.print("Topic: ");   Serial.println(topic);

        const char* response = json_handler_->parseMessage(payload, length, device_id_, modules_);
        publish(config_.topic_response, response);
    }

private:
    static constexpr unsigned long RECONNECT_INTERVAL_MS = 5000;

    WiFiClient      espClient_;
    PubSubClient    client_;
    JsonHandler*    json_handler_      = nullptr;
    SettingHandler* modules_           = nullptr;
    char            device_id_[8]      = {};
    Config          config_            = {};
    bool            time_synced_       = false;
    unsigned long   last_reconnect_ms_ = 0;

    WifiMqttManager() : client_(espClient_) {}

    bool connectToWiFi() {
        if (WiFi.status() == WL_CONNECTED) return true;

        WiFi.disconnect(true);
        WiFi.begin(config_.ssid, config_.password);

        for (int attempt = 0; attempt < config_.max_wifi_attempts && WiFi.status() != WL_CONNECTED; attempt++) {
            Serial.printf("connectToWiFi: attempt %d...\n", attempt + 1);
            delay(500);
        }

        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("connectToWiFi: failed");
            return false;
        }
        Serial.println("connectToWiFi: connected");
        if (!time_synced_) {
            syncTimeFromNTP(config_.utc_offset_sec);
            time_synced_ = true;
        }
        return true;
    }

    bool connectToMQTT() {
        if (client_.connected()) return true;
        if (WiFi.status() != WL_CONNECTED) return false;

        char clientId[16];
        snprintf(clientId, sizeof(clientId), "ESP32_%s", device_id_);

        for (int attempt = 0; attempt < config_.max_mqtt_attempts && !client_.connected(); attempt++) {
            Serial.printf("connectToMQTT: attempt %d...\n", attempt + 1);
            if (client_.connect(clientId, config_.user, config_.mqtt_pass)) {
                client_.subscribe(config_.topic_modules);
                Serial.println("connectToMQTT: connected");
                return true;
            }
            Serial.printf("connectToMQTT: failed, state=%d\n", client_.state());
            delay(500);
        }
        Serial.println("connectToMQTT: couldn't connect");
        return false;
    }

    static void mqttCallback(char* topic, byte* payload, unsigned int length) {
        instance().handleMessage(topic, payload, length);
    }
};
