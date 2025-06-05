//
// Created by xiaol on 2024/8/31.
//

#include "ChargerChannel.hpp"
#include "SampleTask.hpp"
#include "adc.h"
#include "hrtim.h"
#include "main.h"

namespace MainTask
{
//    ChargerChannel channel2 = ChargerChannel(
//            HRTIM_TIMERID_TIMER_B, HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2,
//            IncrementalPID(0.0f, 0.001f, 0.0005f, 0.0f),
//            -0.0081527f, 26.03f, -0.0102f, 20.8632f
//    );
ChargerChannel chargerChannels[] = {ChargerChannel(HRTIM_TIMERID_TIMER_A,
                                                   HRTIM_OUTPUT_TA1,
                                                   IncrementalPID(0.0f, 0.001f, 0.0005f, 0.0f),
                                                   &Tasks::SampleTask::voltageOut[0],
                                                   &Tasks::SampleTask::currentData[0]),
                                    ChargerChannel(HRTIM_TIMERID_TIMER_A,
                                                   HRTIM_OUTPUT_TA2,
                                                   IncrementalPID(0.0f, 0.001f, 0.0005f, 0.0f),
                                                   &Tasks::SampleTask::voltageOut[1],
                                                   &Tasks::SampleTask::currentData[1])};

void initChargerChannels()
{
    chargerChannels[0].initChannel(&hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP1xR,
                                   &hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP3xR);
    chargerChannels[1].initChannel(&hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP2xR,
                                   &hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP4xR);
}

void updateChargers() {}

void checkError() {}

volatile static float testDuty = 0;

void init()
{
    hhrtim1.Instance->sCommonRegs.ODISR |= HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2 | HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2;
    HAL_Delay(100);
    __HAL_HRTIM_MASTER_ENABLE_IT(&hhrtim1, HRTIM_MASTER_IT_MREP);  // enable master repetition interrupt
    HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_MASTER);
    HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
    HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_B);
    HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_C);
    initChargerChannels();
    Tasks::SampleTask::initSampleTask();

    chargerChannels[0].channelEnableOutput();
}

void loop() { chargerChannels[0].channelSetPWM(chargerChannels[0].tempDuty); }
}  // namespace MainTask

extern "C"
{
    [[noreturn]] void systemStart()
    {
        MainTask::init();
        for (;;)
            MainTask::loop();
    }

    void HRTIM1_Master_IRQHandler()
    {
        Tasks::SampleTask::updateSampleDataFromBuffer();
        __HAL_HRTIM_MASTER_CLEAR_IT(&hhrtim1, HRTIM_MASTER_IT_MREP);
    }
}
