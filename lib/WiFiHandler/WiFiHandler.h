#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include "config.h"

class WiFiHandler {
public:
    WiFiHandler();
    bool connect();
    bool isConnected();
};

#endif