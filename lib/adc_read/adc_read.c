#include "adc_read.h"

uint8_t convertSoilMoisture(uint32_t adcValue)
{
    // Convert the ADC value to soil moisture percentage
    static uint8_t sensorValue = 0;

    // Assuming the sensorValue is in the range of 0-100
    // Convert the ADC value to a percentage
    sensorValue = 100 - (adcValue * 100) / 4095;
    return sensorValue;
}

uint8_t convertRainWater(uint32_t adcValue)
{
    // Convert the ADC value to rainwater percentage
    static uint8_t sensorValue = 0;

    // Assuming the sensorValue is in the range of 0-100
    // Convert the ADC value to a percentage
    sensorValue = (adcValue * 100) / 4095;
    return sensorValue;
}