/**
 * @file buzzer.hpp
 * @author JIANG Yicheng RM2023
 * @brief
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023
 */

#pragma once

#include "main.h"
#include "tim.h"

#define BUZZER_TIM htim8
#define BUZZER_TIM_CHANNEL TIM_CHANNEL_4
#define BUZZER_TIM_CHANNEL_CCR CCR4

namespace Buzzer {
/**
 * @brief Initialize the buzzer
 */
    void init();

/**
 * @brief Play a tone
 *
 * @param frequency Frequency of the tone
 */
    inline void play(uint32_t frequency) {
        BUZZER_TIM.Instance->ARR = (uint32_t) ((50000U) / frequency) - 1U;
        BUZZER_TIM.Instance->BUZZER_TIM_CHANNEL_CCR = BUZZER_TIM.Instance->ARR / 2U;
        BUZZER_TIM.Instance->CNT = 0U;
    }

/**
 * @brief Play a tone
 *
 * @param frequency Frequency of the tone
 * @param durationMs Duration in MilliSeconds of the tone
 */
    inline void play(uint32_t frequency, uint32_t durationMs) {
        BUZZER_TIM.Instance->RCR = (durationMs * frequency / 1000U) - 1U;
        BUZZER_TIM.Instance->EGR = TIM_EGR_UG;
        play(frequency);
        __HAL_TIM_CLEAR_FLAG(&BUZZER_TIM, TIM_FLAG_UPDATE);
        __HAL_TIM_ENABLE_IT(&BUZZER_TIM, TIM_IT_UPDATE);
    }

/**
 * @brief Stop playing the tone
 */
    inline void stop() { BUZZER_TIM.Instance->BUZZER_TIM_CHANNEL_CCR = 0U; }
}  // namespace Buzzer