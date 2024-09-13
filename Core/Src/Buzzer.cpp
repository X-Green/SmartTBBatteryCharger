/**
 * @file buzzer.hpp
 * @author JIANG Yicheng RM2023
 * @brief
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023
 */

#include "Buzzer.hpp"


namespace Buzzer
{
void init()
{
    BUZZER_TIM.Instance->BUZZER_TIM_CHANNEL_CCR = 0U;
    HAL_TIMEx_PWMN_Start(&BUZZER_TIM, BUZZER_TIM_CHANNEL);
}

extern "C"
{
    void TIM8_UP_IRQHandler(void)
    {
        __HAL_TIM_CLEAR_FLAG(&htim8, TIM_FLAG_UPDATE);
        __HAL_TIM_DISABLE_IT(&htim8, TIM_IT_UPDATE);
        Buzzer::stop();
    }
}
}  // namespace Buzzer