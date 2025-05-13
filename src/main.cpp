#include <Arduino.h>
#include "Config.h"
#include "WiFiHandler.h"
#include "MQTTHandler.h"
#include "UARTCommunicator.h"
#include "SensorDataParser.h"

WiFiHandler wifiHandler;
MQTTHandler mqttHandler;
UARTCommunicator uartCommunicator;
SensorDataParser dataParser(mqttHandler);

unsigned long previousMillis = 0;
const long interval = 2000; // 2 seconds

void setup() {
    Serial.begin(115200);
    
    wifiHandler.connect();
    mqttHandler.setup();
    uartCommunicator.begin();
}

void loop() {
    unsigned long currentMillis = millis();
    
    // Handle MQTT
    mqttHandler.loop();
    
    // Request data every 2 seconds
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        uartCommunicator.requestData();
    }
    
    // Process incoming UART data
    if (uartCommunicator.dataAvailable()) {
        String data = uartCommunicator.readData();
        if (data.length() > 0 && data.indexOf("TEMP:") != -1) {
            dataParser.parse(data);
        }
    }
}