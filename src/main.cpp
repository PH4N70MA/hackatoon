#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define ZONE1_PIN 23
// Wi-Fi credentials
const char* ssid = "Pixel_8898";
const char* password = "123456789";

// MQTT broker details private
const char* mqtt_broker = "b1b35e1141d346ae810baa94f55377e1.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "smartmeteo";
const char* mqtt_password = "Smartmeteo1";

// MQTT topics
const char* topic_send = "esp32/send";
const char* topic_subscribe = "esp32/zone1"; // Topic to receive messages

// IR Sensor details
const int ir_sensor_pin = 34; // GPIO pin connected to the IR sensor

// Create instances
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

// Variables for timing
long previous_time = 0;

// Callback function to handle incoming messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (String(topic) == "esp32/zone1") {
    digitalWrite(ZONE1_PIN, message == "ON" ? HIGH : LOW);
  }
  // Adaugă și pentru zonele 2 și 3...
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

      // Subscribe to the control topic
      mqttClient.subscribe(topic_subscribe);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  // Initialize secure WiFiClient
  wifiClient.setInsecure(); // Use this only for testing, it allows connecting without a root certificate
  
  setupMQTT();

  pinMode(ir_sensor_pin, INPUT); // Set IR sensor pin as input
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  long now = millis();
  if (now - previous_time > 2000) { // Publish every 10 seconds
    previous_time = now;

    // Read the IR sensor value
    int ir_sensor_value = analogRead(ir_sensor_pin);
    int distance = map(ir_sensor_value, 0, 4095, 0, 30);
    
    // Convert the value to a string
    String ir_value_str = String(distance);
    
    // Publish the sensor value to the MQTT topic
    Serial.print("hello world ");
    Serial.println(ir_value_str);
    mqttClient.publish(topic_send, ir_value_str.c_str());
  }
}