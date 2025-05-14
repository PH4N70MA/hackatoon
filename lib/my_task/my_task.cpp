#include "my_task.h"

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

float temperature;
float humidity;

void systemSetup(void)
{
    own_stdio_setup();
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;
}

void MyDutyForErverAndEverAgain(void)
{
    delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) 
  {

  }
  else {
    temperature = event.temperature;
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) 
  {

  }
  else 
  {
    humidity = event.relative_humidity;
  }
}

void parsing(const char *command)
{    
    if (!strcmp(command, "panzer"))
    {
        Serial.print("TEMP:");
        Serial.print(temperature);
        Serial.print(" HUM:");
        Serial.print(humidity);
        Serial.println();
    }
}