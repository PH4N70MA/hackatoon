#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "Pixel_8898";
const char* password = "123456789";

// MQTT broker details
const char* mqtt_broker = "b1b35e1141d346ae810baa94f55377e1.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "smartmeteo";
const char* mqtt_password = "Smartmeteo1";

// MQTT topics
const char* topic_air_temp = "esp32/air_temp";
const char* topic_air_humidity = "esp32/air_humidity";
const char* topic_soil_humidity = "esp32/soil_humidity";
const char* topic_precipitation = "esp32/precipitation";
const char* topic_subscribe = "esp32/zone1"; // Topic to receive messages

// Create instances
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

// Variables for timing
long previous_time = 0;
String uartBuffer = "";

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // Handle actuator commands
  if (String(topic) == topic_subscribe) {
    if (message == "SW1") {
      Serial.println("SW1");
      // Add code to turn on the actuator
    } else if (message == "SW2") {
      Serial.println("SW2");
      // Add code to turn off the actuator
    } else if (message == "SW3") {
      Serial.println("SW3");
      // Add code to toggle the actuator
    }
  }
}

void setupMQTT() {
  mqttClient.setServer(mqtt_broker, mqtt_port);
  mqttClient.setCallback(mqttCallback);
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
    Serial.println("Reconnecting to MQTT Broker...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT Broker.");
      // Subscribe to control topics
      mqttClient.subscribe(topic_subscribe);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void parseSensorData(String data) {
  // Expected format: "TEMP:25.5 HUM:60.5 SOIL:45.0 RAIN:1.2"
  int tempStart = data.indexOf("TEMP:") + 5;
  int tempEnd = data.indexOf(" ", tempStart);
  float airTemp = data.substring(tempStart, tempEnd).toFloat();
  
  int humStart = data.indexOf("HUM:") + 4;
  int humEnd = data.indexOf(" ", humStart);
  float airHumidity = data.substring(humStart, humEnd).toFloat();
  
  int soilStart = data.indexOf("SOIL:") + 5;
  int soilEnd = data.indexOf(" ", soilStart);
  float soilHumidity = data.substring(soilStart, soilEnd).toFloat();
  
  int rainStart = data.indexOf("RAIN:") + 5;
  float precipitation = data.substring(rainStart).toFloat();

  // Publish sensor data to MQTT
  mqttClient.publish(topic_air_temp, String(airTemp).c_str());
  mqttClient.publish(topic_air_humidity, String(airHumidity).c_str());
  mqttClient.publish(topic_soil_humidity, String(soilHumidity).c_str());
  mqttClient.publish(topic_precipitation, String(precipitation).c_str());

  Serial.println("Date primite de la STM32:");
  Serial.print("Temperatura aer: "); Serial.println(airTemp);
  Serial.print("Umiditate aer: "); Serial.println(airHumidity);
  Serial.print("Umiditate sol: "); Serial.println(soilHumidity);
  Serial.print("Precipitatii: "); Serial.println(precipitation);
}

void setup() {
  Serial.begin(115200);     // Serial for debugging
  Serial1.begin(115200, SERIAL_8N1, 16, 17);  // UART to STM32 (RX=16, TX=17)
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  wifiClient.setInsecure(); // Use this only for testing
  setupMQTT();
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  // Request and receive data from STM32 every 2 seconds
  long now = millis();
  if (now - previous_time > 2000) {
    previous_time = now;
    
    // Send request to STM32
    Serial1.println("hesoyam");
    Serial.println("Trimis request către STM32: hesoyam");
  }

  // Read data from STM32
  while (Serial1.available()) {
    char c = Serial1.read();
    if (c == '\n') {
      if (uartBuffer.length() > 0) {
        Serial.print("Primit de la STM32: ");
        Serial.println(uartBuffer);
        
        // Check if this is sensor data response
        if (uartBuffer.indexOf("TEMP:") != -1) {
          parseSensorData(uartBuffer);
        }
        
        uartBuffer = "";
      }
    } else if (c != '\r') {
      uartBuffer += c;
    }
  }
}