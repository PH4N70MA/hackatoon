#ifndef SENSOR_DATA_PARSER_H
#define SENSOR_DATA_PARSER_H

#include <Arduino.h>
#include "MQTTHandler.h"

class SensorDataParser {
public:
    SensorDataParser(MQTTHandler& handler);
    void parse(String data);

private:
    MQTTHandler& mqttHandler;
};

#endif
