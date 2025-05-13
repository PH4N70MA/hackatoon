#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "config.h"

class MQTTHandler {
private:
    WiFiClientSecure wifiClient;
    PubSubClient mqttClient;
    void callback(char* topic, byte* payload, unsigned int length);
    
public:
    MQTTHandler();
    void setup();
    bool reconnect();
    void loop();
    void publish(const char* topic, const char* message);
};

#endif