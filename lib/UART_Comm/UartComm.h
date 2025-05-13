#ifndef UART_COMM_H
#define UART_COMM_H

#include <Arduino.h>
void uart_init();
String uart_request(const String& cmd);

#endif
