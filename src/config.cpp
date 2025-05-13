#include "Config.h"

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
const char* topic_subscribe = "esp32/zone1";

// UART Configuration
const int uart_rx_pin = 16;
const int uart_tx_pin = 17;
const long uart_baudrate = 115200;