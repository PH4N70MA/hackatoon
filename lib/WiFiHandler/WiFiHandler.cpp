#include "WiFiHandler.h"
#include "config.h"

// Ensure ssid and password are declared, for example:
extern const char* ssid;
extern const char* password;


WiFiHandler::WiFiHandler() {
    // Constructor
}

bool WiFiHandler::connect() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
    return true;
}

bool WiFiHandler::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}