//
// Created by eeasee on 4/2/25.
//

#pragma once

#include "main.h"

namespace ChargerCommon {
    /**
 * Rank: 0->I_IN, 1->IB, 2->IA
 */
    volatile inline uint16_t adc1Buffer[3] = {};

    volatile inline float testDuty = 0.5f;

    volatile inline float voltageInput = 0.0f;

}