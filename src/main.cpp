#include <Arduino.h>
#include "Config.h"
#include "WiFiHandler.h"
#include "MQTTHandler.h"
#include "UARTCommunicator.h"
#include "SensorDataParser.h"

#ifdef ESP32
#include <esp_core_dump.h>
#endif

WiFiHandler wifiHandler;
MQTTHandler mqttHandler;
UARTCommunicator uartCommunicator;
SensorDataParser dataParser(mqttHandler);

enum State {
    SEND_HESOYAM,
    WAIT_HESOYAM_RESPONSE,
    SEND_PANZER,
    WAIT_PANZER_RESPONSE
};

State currentState = SEND_HESOYAM;
unsigned long stateStartTime = 0;
bool receivedExpectedData = false;

void setup() {
    Serial.begin(115200);

    wifiHandler.connect();
    mqttHandler.setup();
    uartCommunicator.begin();  // Default 115200
}

void loop() {
    unsigned long currentMillis = millis();

    mqttHandler.loop();

    // Procesare date UART
    if (uartCommunicator.dataAvailable()) {
        String data = uartCommunicator.readData();

        if (data.length() > 0) {
            dataParser.parse(data);

            // Verificăm datele în funcție de stare
            switch (currentState) {
                case WAIT_HESOYAM_RESPONSE:
                    if (data.indexOf("SOIL:") != -1 && data.indexOf("RAIN:") != -1) {
                        receivedExpectedData = true;
                        stateStartTime = currentMillis;
                        currentState = SEND_PANZER;
                        
                    }
                    break;

                case WAIT_PANZER_RESPONSE:
                    if (data.indexOf("TEMP:") != -1 && data.indexOf("HUM:") != -1) {
                        receivedExpectedData = true;
                        stateStartTime = currentMillis;
                        currentState = SEND_HESOYAM;
                        
                    }
                    break;

                default:
                    break;
            }
        }
    }

    // FSM – control comenzi
    switch (currentState) {
        case SEND_HESOYAM:
            uartCommunicator.send("hesoyam\n");
            
            stateStartTime = currentMillis;
            receivedExpectedData = false;
            currentState = WAIT_HESOYAM_RESPONSE;
            break;

        case WAIT_HESOYAM_RESPONSE:
            if (!receivedExpectedData && currentMillis - stateStartTime >= 5000) {
                
                currentState = SEND_HESOYAM;
            }
            break;

        case SEND_PANZER:
            uartCommunicator.send("panzer\n");
            //
            stateStartTime = currentMillis;
            receivedExpectedData = false;
            currentState = WAIT_PANZER_RESPONSE;
            break;

        case WAIT_PANZER_RESPONSE:
            if (!receivedExpectedData && currentMillis - stateStartTime >= 5000) {
                
            
                currentState = SEND_PANZER;
            }
            break;
    }
}
