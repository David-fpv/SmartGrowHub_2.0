#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>
#include "setting_handler.h"
#include "json_handler.h"


// Wi-Fi settings
const char* ssid = "David phone 2a";
const char* password = "qwerty555";

// MQTT settings
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char* mqttUser = "";  // Укажите, если требуется
const char* mqttPassword = "";  // Укажите, если требуется

// Objects
WiFiClient espClient;
PubSubClient client(espClient);
JsonHandler *json_mqtt_handler;
SettingHandler *modules_mqtt;


void callback(char* topic, byte payload[], unsigned int length);
void setupWiFiMQTT();
void WiFiMQTT_reconnecter();
void mqttPublishInfo(std::string message);
void wifi_mqtt_loop();
void injectMqttDependencies(SettingHandler* modules, JsonHandler *json_handler);


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

    modules_mqtt->SetProgram(json_mqtt_handler->parseProgram(message));
}


void injectMqttDependencies(SettingHandler* modules, JsonHandler *json_handler)
{
    modules_mqtt = modules;
    json_mqtt_handler = json_handler;
}


void connectToMQTT()
{
    int attempt = 0;
    while (!client.connected() && attempt < 10)
    {
        attempt++;

        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32_Client", mqttUser, mqttPassword))
        {
            Serial.println("MQtt connected!");
            client.subscribe("/Gomel/Tar/modules/"); 
            Serial.println("The subscription was completed successfully");
        }
        else
        {
            Serial.print("Error connect: ");
            Serial.print(client.state());
            delay(100);
        }
    }

    if (!client.connected()) {
        Serial.println("Failed to connect to MQTT after multiple attempts.");
    }
}


void setupWiFiMQTT()
{
    // Подключение к Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Wi-Fi conncted!");

    // Подключение к MQTT
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback); // Установка функции обратного вызова
    client.setBufferSize(1000);

    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32_Client", mqttUser, mqttPassword))
        {
            Serial.println("MQtt connected!");
            client.subscribe("/Gomel/Tar/modules/"); 
            Serial.println("The subscription was completed successfully");
        }
        else
        {
            Serial.print("Error connect: ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void WiFiMQTT_reconnecter()
{
    // Подключение к Wi-Fi
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, password);
    }
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to Wi-Fi...");
    }

    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32_Client", mqttUser, mqttPassword))
        {
            Serial.println("MQtt connected!");
            client.subscribe("/Gomel/Tar/modules/");
            Serial.println("The subscription was completed successfully");
        }
        else
        {
            Serial.print("Error connect: ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void mqttPublishInfo(std::string message)
{
    Serial.print("WiFi status: ");
    Serial.println(WiFi.status() == WL_CONNECTED);

    Serial.print("MQTT status: ");
    Serial.println(client.connected());

    WiFiMQTT_reconnecter();
    client.publish("/Gomel/Tar/sensors/", message.c_str());
}

void wifi_mqtt_loop()
{
    client.loop();
    WiFiMQTT_reconnecter();
}