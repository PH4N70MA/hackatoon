#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define ZONE1_PIN 23

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

// Pin definitions for sensors (modify according to your setup)
const int airTempPin = 34;    // Analog pin for air temperature sensor
const int airHumidityPin = 35; // Analog pin for air humidity sensor
const int soilHumidityPin = 32; // Analog pin for soil humidity sensor
const int precipitationPin = 33; // Analog pin for precipitation sensor

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
      mqttClient.subscribe(topic_subscribe);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Function to read sensor values
float readAirTemperature() {
  // Implement your actual sensor reading logic here
  // Example for analog sensor:
  int rawValue = analogRead(airTempPin);
  // Convert raw value to temperature (adjust formula according to your sensor)
  float temperature = (rawValue * 0.48828125) - 50.0; // Example conversion
  return temperature;
}

float readAirHumidity() {
  // Implement your actual sensor reading logic here
  int rawValue = analogRead(airHumidityPin);
  // Convert raw value to humidity percentage (adjust formula)
  float humidity = (rawValue * 100.0) / 4095.0; // Example conversion
  return humidity;
}

float readSoilHumidity() {
  // Implement your actual sensor reading logic here
  int rawValue = analogRead(soilHumidityPin);
  // Convert raw value to soil humidity percentage (adjust formula)
  float humidity = (rawValue * 100.0) / 4095.0; // Example conversion
  return humidity;
}

float readPrecipitation() {
  // Implement your actual sensor reading logic here
  int rawValue = analogRead(precipitationPin);
  // Convert raw value to precipitation (adjust formula)
  float precipitation = rawValue / 100.0; // Example conversion
  return precipitation;
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

  wifiClient.setInsecure(); // Use this only for testing
  
  setupMQTT();

  pinMode(ZONE1_PIN, OUTPUT);
  
  // Initialize sensor pins
  pinMode(airTempPin, INPUT);
  pinMode(airHumidityPin, INPUT);
  pinMode(soilHumidityPin, INPUT);
  pinMode(precipitationPin, INPUT);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  long now = millis();
  if (now - previous_time > 2000) { // Send data every 2 seconds
    previous_time = now;

    // Read actual sensor values
    float airTemp = readAirTemperature();
    float airHumidity = readAirHumidity();
    float soilHumidity = readSoilHumidity();
    float precipitation = readPrecipitation();

    // Send values to corresponding topics
    mqttClient.publish(topic_air_temp, String(airTemp).c_str());
    mqttClient.publish(topic_air_humidity, String(airHumidity).c_str());
    mqttClient.publish(topic_soil_humidity, String(soilHumidity).c_str());
    mqttClient.publish(topic_precipitation, String(precipitation).c_str());

    Serial.println("Date trimise:");
    Serial.print("Temperatura aer: "); Serial.println(airTemp);
    Serial.print("Umiditate aer: "); Serial.println(airHumidity);
    Serial.print("Umiditate sol: "); Serial.println(soilHumidity);
    Serial.print("Precipitatii: "); Serial.println(precipitation);
  }
}