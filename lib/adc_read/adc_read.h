#ifndef ADC_UTILS_H
#define ADC_UTILS_H

#include <stdint.h> // For uint16_t
#include "main.h" // Include this to access `hadc1` and other shared variables

uint8_t convertSoilMoisture(uint32_t adcValue);
uint8_t convertRainWater(uint32_t adcValue);

#endif // ADC_UTILS_H