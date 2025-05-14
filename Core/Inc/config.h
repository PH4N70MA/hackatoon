#ifndef CONFIG_H
#define CONFIG_H

// Configuration settings for the project

#define RX_DATA_SIZE 10
#define DEBOUNDE_DELAY 100

#define RELAY_1_PORT GPIOB
#define RELAY_2_PORT GPIOB
#define RELAY_3_PORT GPIOB

#define RELAY_1_PIN GPIO_PIN_7
#define RELAY_2_PIN GPIO_PIN_8
#define RELAY_3_PIN GPIO_PIN_9

char buf[100];
uint8_t RX_DATA[RX_DATA_SIZE];

#endif // CONFIG_H