#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>
#include "setting_handler.h"
#include "json_handler.h"

// Wi-Fi settings
const char *ssid = "DAVID-laptop";
const char *password = "qwerty555";
const int max_connection_attempt_wifi = 20;

// MQTT settings
const char *mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char *mqttUser = "";     // Set it if necessary
const char *mqttPassword = ""; // Set it if necessary
const int max_connection_attempt_mqtt = 10;

// Objects
WiFiClient espClient;
PubSubClient client(espClient);
JsonHandler *json_mqtt_handler;
SettingHandler *modules_mqtt;
std::string device_id_number;

void callback(char *topic, byte payload[], unsigned int length);
bool connectToWiFi();
bool connectToMQTT();
void setupWiFiMQTT();
bool WiFiMQTT_connecter();
void mqttPublishInfo(std::string message);
void mqttPublish(std::string topic, std::string message);
void wifi_mqtt_loop();
void injectMqttDependencies(SettingHandler *modules, JsonHandler *json_handler);

void callback(char *topic, byte payload[], unsigned int length)
{
    std::string message;
    Serial.print("Topic: ");
    Serial.println(topic);

    Serial.print("Message: ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
        message += (char)payload[i];
    }
    Serial.println();

    std::string output_message = json_mqtt_handler->parseMessage(message, device_id_number, modules_mqtt);
    mqttPublish("/Gomel/Tar/sensors/", output_message);
}

void injectMqttDependencies(SettingHandler *modules, JsonHandler *json_handler, std::string device_id)
{
    modules_mqtt = modules;
    json_mqtt_handler = json_handler;
    device_id_number = device_id;
}

bool connectToWiFi()
{
    int attempt_count = 0;

    // Check connection to WiFi
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, password);

        while ((WiFi.status() != WL_CONNECTED) && (attempt_count <= max_connection_attempt_wifi))
        {
            attempt_count++;
            Serial.print("connectToWiFi: ");
            Serial.print(attempt_count + 1);
            Serial.println(". Connecting to Wi-Fi...");
            delay(500);
        }

        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("connectToWiFi: Couldn't connect to Wi-Fi");
            return false;
        }
    }
    Serial.println("connectToWiFi: Wi-Fi connected");
    return true;
}

bool connectToMQTT()
{
    int attempt_count = 0;
    bool flag = true;
    while (!client.connected() && (attempt_count < max_connection_attempt_mqtt))
    {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32_Client", mqttUser, mqttPassword))
        {
            Serial.println("MQtt connected!");
            client.subscribe("/Gomel/Tar/modules/");
            Serial.println("The subscription was completed successfully");
            flag = true;
            break;
        }
        else
        {
            Serial.print("connectToMQTT: ");
            Serial.print(attempt_count + 1);
            Serial.print(". MQTT error connect: ");
            Serial.println(client.state());
            attempt_count++;
            flag = false;
            delay(2000);
        }
    }

    if (flag == false)
    {
        Serial.println("connectToMQTT: Couldn't connect to MQTT");
        return false;
    }

    Serial.println("connectToMQTT: MQTT connected");
    return true;
}

void setupWiFiMQTT()
{
    // MQTT settings
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback); // Set callback function
    client.setBufferSize(1000);

    WiFiMQTT_connecter();
}

bool WiFiMQTT_connecter()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        if (connectToWiFi() == false)
        {
            return false;
        }
    }

    if (!client.connected())
    {
        return connectToMQTT();
    }

    return true;
}

void mqttPublishInfo(std::string message)
{
    Serial.print("WiFi status: ");
    Serial.println(WiFi.status() == WL_CONNECTED);

    Serial.print("MQTT status: ");
    Serial.println(client.connected());

    WiFiMQTT_connecter();
    client.publish("/Gomel/Tar/sensors/", message.c_str());
}

void mqttPublish(std::string topic, std::string message)
{
    Serial.print("WiFi status: ");
    Serial.println(WiFi.status() == WL_CONNECTED);

    Serial.print("MQTT status: ");
    Serial.println(client.connected());

    WiFiMQTT_connecter();
    client.publish(topic.c_str(), message.c_str());
}

void wifi_mqtt_loop()
{
    client.loop();
    WiFiMQTT_connecter();
}