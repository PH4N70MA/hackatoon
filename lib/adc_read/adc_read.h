#ifndef ADC_UTILS_H
#define ADC_UTILS_H

#include <stdint.h> // For uint16_t
#include "main.h" // Include this to access `hadc1` and other shared variables

// Declare the function
void readADC(ADC_HandleTypeDef *hadc1, uint32_t *value1, uint32_t *value2);

#endif // ADC_UTILS_H