#ifndef ACTUATOR_H
#define ACTUATOR_H

// Includes
#include <main.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "config.h"


// Enum for relay states
typedef enum {
    RELAY_OFF,
    RELAY_ON,
    RELAY_TOGGLE
} RelayState;

// Structure for relay control
typedef struct {
    GPIO_TypeDef *port; // GPIO port
    uint16_t pin;       // GPIO pin
    RelayState state;   // Current state of the relay
} RelayControl;

void initRelayControl(RelayControl *relay, GPIO_TypeDef *port, uint16_t pin);
void setRelayState(RelayControl *relay, RelayState state);
void toggle(RelayControl *relay);
void turnOn(RelayControl *relay);
void turnOff(RelayControl *relay);
void getRelayState(RelayControl *relay, RelayState *state);

#endif // ACTUATOR_H