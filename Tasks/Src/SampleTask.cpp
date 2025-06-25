//
// Created by eeasee on 6/5/25.
//
#include "SampleTask.hpp"

#include "MathUtil.hpp"
#include "adc.h"

namespace Tasks::SampleTask
{

void initSampleTask()
{
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_Delay(100);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
    HAL_Delay(100);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1Buffer, 7 * 4);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc2Buffer, 6);
}

void updateSampleDataFromBuffer()
{
    // Process V from ADC1
    for (int i = 0; i < 7; ++i)
    {
        float tmpVoltageData = ((float)adc1Buffer[i]) * VOLTAGE_GAIN + VOLTAGE_BIAS;
        voltageOut[i]        = voltageOut[i] * VOLTAGE_LPF_ALPHA + tmpVoltageData * (1.0f - VOLTAGE_LPF_ALPHA);
        voltageOut[i]        = M_MAX(voltageOut[i], 0.1f);
    }
    voltageIn = voltageOut[6];

    // Process I from ADC2
    for (int i = 0; i < 6; ++i)
    {
        float tmpCurrentData = (float)adc2Buffer[i] * CURRENT_GAIN + CURRENT_BIAS;
        currentData[i]       = currentData[i] * CURRENT_LPF_ALPHA + tmpCurrentData * (1.0f - CURRENT_LPF_ALPHA);
        currentData[i]       = M_MAX(currentData[i], 0.02f);
    }
}
}  // namespace Tasks::SampleTask