#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>
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
              const std::string& device_id, const Config& config) {
        modules_      = modules;
        json_handler_ = json_handler;
        device_id_    = device_id;
        config_       = config;
    }

    void setup() {
        client_.setServer(config_.server, config_.port);
        client_.setCallback(mqttCallback);
        client_.setBufferSize(config_.mqtt_buffer_size);
        ensureConnected();
    }

    void loop() {
        client_.loop();
        ensureConnected();
    }

    void publish(const std::string& topic, const std::string& message) {
        ensureConnected();
        client_.publish(topic.c_str(), message.c_str());
    }

    void publishInfo(const std::string& message) {
        publish(config_.topic_sensors, message);
    }

    void handleMessage(const char* topic, byte* payload, unsigned int length) {
        std::string message(reinterpret_cast<const char*>(payload), length);
        Serial.print("Topic: ");   Serial.println(topic);
        Serial.print("Message: "); Serial.println(message.c_str());

        std::string response = json_handler_->parseMessage(message, device_id_, modules_);
        publish(config_.topic_sensors, response);
    }

private:
    WiFiClient     espClient_;
    PubSubClient   client_;
    JsonHandler*   json_handler_ = nullptr;
    SettingHandler* modules_     = nullptr;
    std::string    device_id_;
    Config         config_       = {};
    bool           time_synced_  = false;

    WifiMqttManager() : client_(espClient_) {}

    bool connectToWiFi() {
        if (WiFi.status() == WL_CONNECTED) return true;

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
        std::string clientId = "ESP32_" + device_id_;
        for (int attempt = 0; attempt < config_.max_mqtt_attempts && !client_.connected(); attempt++) {
            Serial.printf("connectToMQTT: attempt %d...\n", attempt + 1);
            if (client_.connect(clientId.c_str(), config_.user, config_.mqtt_pass)) {
                client_.subscribe(config_.topic_modules);
                Serial.println("connectToMQTT: connected");
                return true;
            }
            Serial.printf("connectToMQTT: failed, state=%d\n", client_.state());
            delay(2000);
        }
        if (!client_.connected()) {
            Serial.println("connectToMQTT: couldn't connect");
            return false;
        }
        return true;
    }

    bool ensureConnected() {
        if (WiFi.status() != WL_CONNECTED && !connectToWiFi()) return false;
        if (!client_.connected()) return connectToMQTT();
        return true;
    }

    static void mqttCallback(char* topic, byte* payload, unsigned int length) {
        instance().handleMessage(topic, payload, length);
    }
};
