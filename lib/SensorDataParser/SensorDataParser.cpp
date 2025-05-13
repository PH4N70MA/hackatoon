#include "SensorDataParser.h"
#include "config.h"

extern const char* topic_air_temp;
extern const char* topic_air_humidity;
extern const char* topic_soil_humidity;
extern const char* topic_precipitation;

SensorDataParser::SensorDataParser(MQTTHandler& handler) : mqttHandler(handler) {}

void SensorDataParser::parse(String data) {
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

    mqttHandler.publish(topic_air_temp, String(airTemp).c_str());
    mqttHandler.publish(topic_air_humidity, String(airHumidity).c_str());
    mqttHandler.publish(topic_soil_humidity, String(soilHumidity).c_str());
    mqttHandler.publish(topic_precipitation, String(precipitation).c_str());

    Serial.println("Data received from STM32:");
    Serial.print("Air Temp: "); Serial.println(airTemp);
    Serial.print("Air Humidity: "); Serial.println(airHumidity);
    Serial.print("Soil Humidity: "); Serial.println(soilHumidity);
    Serial.print("Precipitation: "); Serial.println(precipitation);
}