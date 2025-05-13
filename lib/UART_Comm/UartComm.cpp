#include "UartComm.h"
#include <HardwareSerial.h>

HardwareSerial uart1(1);

void uart_init() {
  uart1.begin(115200, SERIAL_8N1, 16, 17); // RX, TX
}

String uart_request(const String& cmd) {
  uart1.flush();
  uart1.print(cmd + "\n");

  unsigned long start = millis();
  String resp = "";
  while (millis() - start < 1000) {
    if (uart1.available()) {
      resp = uart1.readStringUntil('\n');
      break;
    }
  }
  return resp;
}
