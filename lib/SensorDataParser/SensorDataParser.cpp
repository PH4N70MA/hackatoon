#include "SensorDataParser.h"
#include "config.h"

extern const char* topic_air_temp;
extern const char* topic_air_humidity;
extern const char* topic_soil_humidity;
extern const char* topic_precipitation;

SensorDataParser::SensorDataParser(MQTTHandler& handler) : mqttHandler(handler) {}

void SensorDataParser::parse(String data) {
    if (data.indexOf("TEMP:") == -1 || data.indexOf("HUM:") == -1 || 
        data.indexOf("SOIL:") == -1 || data.indexOf("RAIN:") == -1) {
        Serial.println(data.indexOf("HUM:"));
        return;
    }

    try {
        int temp = data.substring(data.indexOf("TEMP:") + 5, data.indexOf(" ", data.indexOf("TEMP:"))).toInt();
        int hum  = data.substring(data.indexOf("HUM:") + 4,  data.indexOf(" ", data.indexOf("HUM:"))).toInt();
        int soil = data.substring(data.indexOf("SOIL:") + 5, data.indexOf(" ", data.indexOf("SOIL:"))).toInt();
        int rain = data.substring(data.indexOf("RAIN:") + 5).toInt();

        mqttHandler.publish(topic_air_temp, String(temp).c_str());
        mqttHandler.publish(topic_air_humidity, String(hum).c_str());
        mqttHandler.publish(topic_soil_humidity, String(soil).c_str());
        mqttHandler.publish(topic_precipitation, String(rain).c_str());

        Serial.printf("Date parsate: Temp: %d°C | Hum: %d%% | Soil: %d%% | Rain: %dmm\n", temp, hum, soil, rain);
    } 
    catch (...) {
        Serial.println("Eroare la parsare!");
    }
}
