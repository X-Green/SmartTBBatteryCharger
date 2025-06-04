//
// Created by xiaol on 2024/8/31.
//

#include "hrtim.h"
#include "adc.h"
#include "main.h"
#include "ChargerChannel.hpp"
#include "ChargerCommon.hpp"

namespace MainTask {
    ChargerChannel channel2 = ChargerChannel(
            HRTIM_TIMERID_TIMER_B, HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2,
            IncrementalPID(0.0f, 0.001f, 0.0005f, 0.0f),
            -0.0081527f, 26.03f, -0.0102f, 20.8632f
    );

    void updateChargers() {
    }

    void checkError() {
    }



    void init() {
        hhrtim1.Instance->sCommonRegs.ODISR |=
                HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2 | HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2;
//        HAL_OPAMP_Start(&hopamp1);
//        HAL_OPAMP_Start(&hopamp2);
//        HAL_OPAMP_Start(&hopamp6);
        HAL_Delay(100);
        HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
        HAL_Delay(100);
        HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
        HAL_Delay(100);
//        HAL_ADCEx_Calibration_Start(&hadc4, ADC_SINGLE_ENDED);

        HAL_ADC_Start_DMA(&hadc1, (uint32_t *) (ChargerCommon::adc1Buffer), 3);

        HAL_ADC_Start(&hadc2);
//        HAL_ADC_Start(&hadc4);


        __HAL_HRTIM_MASTER_ENABLE_IT(&hhrtim1, HRTIM_MASTER_IT_MREP); // enable master repetition interrupt
        HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_MASTER);
        HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
        HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_B);

        channel2.channelEnableOutput();

        channel2.initChannel(
                &(hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP1xR),
                &(hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_B].CMP3xR)
        );
    }

    /** ADC2/OA2 -> VB */
    uint16_t adc2Value = 0;

    /** ADC4/OA6 -> V_IN */
    uint16_t adc4Value = 0;

    volatile float gain_VIN = 1.0f;
    volatile float bias_VIN = 0.0f;


    void loop() {
        adc2Value = HAL_ADC_GetValue(&hadc2);
//        adc4Value = HAL_ADC_GetValue(&hadc4);
        ChargerCommon::voltageInput = (float) adc4Value * gain_VIN - bias_VIN;
        channel2.setVoltageDataRaw(adc2Value);
        channel2.channelSetPWM(ChargerCommon::testDuty);
    }
}

extern "C" {
[[noreturn]] void systemStart() {
    MainTask::init();
    for (;;) MainTask::loop();
}

void HRTIM1_Master_IRQHandler() {
    __HAL_HRTIM_MASTER_CLEAR_IT(&hhrtim1, HRTIM_MASTER_IT_MREP);
}
}
