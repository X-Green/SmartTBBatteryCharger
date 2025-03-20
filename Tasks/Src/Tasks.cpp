//
// Created by xiaol on 2024/8/31.
//

#include "hrtim.h"
#include "adc.h"
#include "main.h"
#include "opamp.h"
#include "tim.h"

namespace Tasks {

    void updateChargers() {

    }

    void checkError() {

    }

    volatile uint16_t adc1Buffer[3] = {};


    void init() {
        hhrtim1.Instance->sCommonRegs.ODISR |=
                HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2 | HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2;
        HAL_OPAMP_Start(&hopamp1);
        HAL_OPAMP_Start(&hopamp2);
        HAL_OPAMP_Start(&hopamp6);
        HAL_Delay(100);
        HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
        HAL_Delay(100);
        HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
        HAL_Delay(100);
        HAL_ADCEx_Calibration_Start(&hadc4, ADC_SINGLE_ENDED);

        HAL_ADC_Start_DMA(&hadc1, (uint32_t *) (adc1Buffer), 3);

        HAL_ADC_Start(&hadc2);
        HAL_ADC_Start(&hadc4);


        __HAL_HRTIM_MASTER_ENABLE_IT(&hhrtim1, HRTIM_MASTER_IT_MREP);  // enable master repetition interrupt
        HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_MASTER);
        HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
        HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_B);

    }

    static volatile uint16_t adc2Value = 0;
    static volatile uint16_t adc4Value = 0;

    void loop() {
        adc2Value = HAL_ADC_GetValue(&hadc2);
        adc4Value = HAL_ADC_GetValue(&hadc4);
    }
}

extern "C" {
[[noreturn]] void systemStart() {
    Tasks::init();
    for (;;) Tasks::loop();
}

void HRTIM1_Master_IRQHandler() {
    static volatile uint16_t nana = 0;
    nana++;
    __HAL_HRTIM_MASTER_CLEAR_IT(&hhrtim1, HRTIM_MASTER_IT_MREP);
}

}
