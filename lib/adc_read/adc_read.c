#include "adc_read.h"

void readRowADC(ADC_HandleTypeDef *hadc1, uint32_t *value1, uint32_t *value2)
{
    // Reconfigure the ADC channel to IN0
    HAL_ADC_Start(hadc1);
    HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);
    *value1 = HAL_ADC_GetValue(hadc1); // Read data from IN0

    // Reconfigure the ADC channel to IN1
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(hadc1, &sConfig);

    HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);
    *value2 = HAL_ADC_GetValue(hadc1); // Read data from IN1

    // Reconfigure the ADC channel back to IN0 for the next loop iteration
    sConfig.Channel = ADC_CHANNEL_0;
    HAL_ADC_ConfigChannel(hadc1, &sConfig);
}

uint8_t convertSoilMoisture(uint32_t adcValue)
{
    // Convert the ADC value to soil moisture percentage
    static uint8_t sensorValue = 0;

    // Assuming the sensorValue is in the range of 0-100
    // Convert the ADC value to a percentage
    sensorValue = (adcValue * 100) / 4095;
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