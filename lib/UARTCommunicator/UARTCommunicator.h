#ifndef UART_COMMUNICATOR_H
#define UART_COMMUNICATOR_H

#include <HardwareSerial.h>
#include "config.h"

class UARTCommunicator {
private:
    String buffer;
    
public:
    UARTCommunicator();
    void begin();
    void requestData();
    bool dataAvailable();
    String readData();
};

#endif