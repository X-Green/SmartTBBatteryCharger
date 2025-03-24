//
// Created by xiaol on 2024/8/31.
//

#include "hrtim.h"
#include "adc.h"
#include "main.h"
#include "opamp.h"
#include "ChargerChannel.hpp"

namespace Tasks {

    ChargerChannel channel1 = ChargerChannel(
            HRTIM_TIMERID_TIMER_B, HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2,
            IncrementalPID(0.0f, 0.001f, 0.0005f, 0.0f)
    );

    void updateChargers() {

    }

    void checkError() {

    }

    volatile uint16_t adc1Buffer[3] = {};
    static volatile uint32_t *ptr2R_1 = nullptr;


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

        channel1.channelEnableOutput();

        channel1.initChannel(
                &(hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP1xR),
                &(hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP3xR)
        );
    }

    uint16_t adc2Value = 0;
    uint16_t adc4Value = 0;

    static volatile float testDuty = 0.5f;

    void loop() {
        adc2Value = HAL_ADC_GetValue(&hadc2);
        adc4Value = HAL_ADC_GetValue(&hadc4);

        channel1.channelSetPWM(testDuty);
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
