#include "UARTCommunicator.h"
#include "config.h"

extern const int uart_rx_pin;
extern const int uart_tx_pin;
extern const long uart_baudrate;

UARTCommunicator::UARTCommunicator() {}

void UARTCommunicator::begin() {
    Serial1.begin(uart_baudrate, SERIAL_8N1, uart_rx_pin, uart_tx_pin);
}

void UARTCommunicator::requestData() {
    Serial1.println("hesoyam");
    Serial.println("Request sent to STM32: hesoyam");
}

bool UARTCommunicator::dataAvailable() {
    return Serial1.available();
}

String UARTCommunicator::readData() {
    while (Serial1.available()) {
        char c = Serial1.read();
        if (c == '\n') {
            if (buffer.length() > 0) {
                String result = buffer;
                buffer = "";
                return result;
            }
        } else if (c != '\r') {
            buffer += c;
        }
    }
    return "";
}