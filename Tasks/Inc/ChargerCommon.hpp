//
// Created by eeasee on 4/2/25.
//

#pragma once

#include "main.h"

namespace ChargerCommon {
    /**
 * Rank: 0->I_IN, 1->IB, 2->IA
 */
    volatile uint16_t adc1Buffer[3] = {};

    volatile float testDuty = 0.5f;

    volatile float voltageInput = 0.0f;

}