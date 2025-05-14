#include "UARTCommunicator.h"

void UARTCommunicator::begin(unsigned long baud) {
    Serial.begin(baud); // UART2 pe ESP32. Poți modifica dacă folosești alți pini.
}

void UARTCommunicator::send(const String& message) {
    Serial.print(message);
}

bool UARTCommunicator::dataAvailable() {
    return Serial.available() > 0;
}

String UARTCommunicator::readData() {
    String data = "";
    while (Serial.available()) {
        char c = Serial.read();
        data += c;
    }
    return data;
}
