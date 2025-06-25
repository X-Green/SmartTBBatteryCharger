//
// Created by eeasee on 6/4/25.
//

#pragma once
#include "main.h"

namespace Tasks::SampleTask
{

/**
 * Voltage: [A1 A2 B1 B2 C1 C2 VIN]
 */
inline uint16_t adc1Buffer[7]     = {};
constexpr float VOLTAGE_GAIN      = 29.0f / 4096.0f;
constexpr float VOLTAGE_BIAS      = 0.12f;
constexpr float VOLTAGE_LPF_ALPHA = 0.5f;
inline float voltageOut[7]       = {};
inline float voltageIn            = 0.0f;

/**
 * Current: [A1 A2 B1 B2 C1 C2]
 */
inline uint16_t adc2Buffer[6]     = {};
constexpr float CURRENT_GAIN      = 14.5f / 4096.0f;
constexpr float CURRENT_BIAS      = 0.0f;
constexpr float CURRENT_LPF_ALPHA = 0.5f;
inline float currentData[6]       = {};

void initSampleTask();

void updateSampleDataFromBuffer();
}  // namespace Tasks::SampleTask