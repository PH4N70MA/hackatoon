#include "MQTTHandler.h"
#include "config.h"


extern const char* mqtt_broker;
extern const int mqtt_port;
extern const char* mqtt_username;
extern const char* mqtt_password;
extern const char* topic_subscribe;



MQTTHandler::MQTTHandler() : mqttClient(wifiClient) {}


void MQTTHandler::setup() {
    wifiClient.setInsecure(); // For testing only
    mqttClient.setServer(mqtt_broker, mqtt_port);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->callback(topic, payload, length);
    });
}

void MQTTHandler::callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    
    Serial.print("Message [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(message);

    if (String(topic) == topic_subscribe) {
        if (message == "SW1") {
            Serial.println("SW1 command received");
        } else if (message == "SW2") {
            Serial.println("SW2 command received");
        } else if (message == "SW3") {
            Serial.println("SW3 command received");
        }
    }
}

bool MQTTHandler::reconnect() {
    if (mqttClient.connected()) return true;
    
    Serial.println("Connecting to MQTT Broker...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
        mqttClient.subscribe(topic_subscribe);
        return true;
    }
    return false;
}

void MQTTHandler::loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();
}

void MQTTHandler::publish(const char* topic, const char* message) {
    mqttClient.publish(topic, message);
}