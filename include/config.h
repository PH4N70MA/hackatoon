#ifndef CONFIG_H
#define CONFIG_H

// Wi-Fi credentials
extern const char* ssid;
extern const char* password;

// MQTT broker details
extern const char* mqtt_broker;
extern const int mqtt_port;
extern const char* mqtt_username;
extern const char* mqtt_password;

// MQTT topics
extern const char* topic_air_temp;
extern const char* topic_air_humidity;
extern const char* topic_soil_humidity;
extern const char* topic_precipitation;
extern const char* topic_subscribe;

// UART Configuration
extern const int uart_rx_pin;
extern const int uart_tx_pin;
extern const long uart_baudrate;

#endif