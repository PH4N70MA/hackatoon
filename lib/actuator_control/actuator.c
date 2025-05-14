// actuator.c
// Actuator control module
// Author: [Your Name]
// Date: [Date]

#include "actuator.h"

void initRelayControl(RelayControl *relay, GPIO_TypeDef *port, uint16_t pin) 
{
    relay->port = port;
    relay->pin = pin;
    relay->state = RELAY_OFF;

    // Initialize the GPIO pin
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void setRelayState(RelayControl *relay, RelayState state) 
{
    relay->state = state;

    if (state == RELAY_ON) 
    {
        HAL_GPIO_WritePin(relay->port, relay->pin, GPIO_PIN_SET);
    } 
    else if (state == RELAY_OFF) 
    {
        HAL_GPIO_WritePin(relay->port, relay->pin, GPIO_PIN_RESET);
    }
}

void toggle(RelayControl *relay) 
{
    if (relay->state == RELAY_ON) 
    {
        setRelayState(relay, RELAY_OFF);
    } 
    else 
    {
        setRelayState(relay, RELAY_ON);
    }
}

void turnOn(RelayControl *relay) 
{
    setRelayState(relay, RELAY_ON);
}

void turnOff(RelayControl *relay) 
{
    setRelayState(relay, RELAY_OFF);
}

void getRelayState(RelayControl *relay, RelayState *state) 
{
    *state = relay->state;
}