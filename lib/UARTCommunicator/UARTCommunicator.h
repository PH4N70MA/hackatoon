#ifndef UART_COMMUNICATOR_H
#define UART_COMMUNICATOR_H

#include <Arduino.h>

class UARTCommunicator {
public:
    void begin(unsigned long baud = 115200);  // inițializare UART
    void send(const String& message);         // trimite mesaj
    bool dataAvailable();                     // verifică dacă sunt date disponibile
    String readData();                        // citește datele primite
};

#endif
