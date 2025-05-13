#ifndef SENSOR_DATA_PARSER_H
#define SENSOR_DATA_PARSER_H

#include "MQTTHandler.h"

class SensorDataParser {
private:
    MQTTHandler& mqttHandler;
    
public:
    SensorDataParser(MQTTHandler& handler);
    void parse(String data);
};

#endif