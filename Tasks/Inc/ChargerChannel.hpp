//
// Created by xiaol on 2025/3/20.
//

#pragma once

#include "IncrementalPID.hpp"
#include "hrtim.h"
#include "main.h"

class ChargerChannel
{
   public:
    const uint32_t HRTIM_PERIOD = 53760;

    const uint32_t HRTIM_TIMERID;
    const uint32_t HRTIM_OUTPUT_CHANNEL_IDENTIFIER;

    volatile uint32_t *pRegCMPRise;
    volatile uint32_t *pRegCMPFall;

    float *const pVoltageOut;
    float *const pCurrentOut;

    bool errorOCFlag     = false;
    bool errorShortFlag  = false;
    bool errorOVFlag     = false;
    bool errorSupplyFlag = false;

    float targetCurrent = 0.0f;
    float targetVoltage = 26.1f;
    float tempDuty      = 0.0f;

    enum ChannelState
    {
        IDLE,
        CHARGING,
        ERROR_STATE
    };

    ChannelState state = IDLE;

    IncrementalPID pidCurrent;

    IncrementalPID pidVoltage;

    void updateChannelStatus();

    void updateChannelDCDC();

    void updateChannelError();

    ChargerChannel(uint32_t hrtimTimerid,
                   uint32_t hrtimOutputChannelIdentifier,
                   IncrementalPID pidCurrent,
                   IncrementalPID pidVoltage,
                   float *pVoltageData,
                   float *pCurrentData)

        : HRTIM_TIMERID(hrtimTimerid),
          HRTIM_OUTPUT_CHANNEL_IDENTIFIER(hrtimOutputChannelIdentifier),
          pRegCMPRise(nullptr),
          pRegCMPFall(nullptr),
          pVoltageOut(pVoltageData),
          pCurrentOut(pCurrentData),
          pidCurrent(pidCurrent),
          pidVoltage(pidVoltage)
    {
    }

    void initChannel(volatile uint32_t *regCmpRise, volatile uint32_t *regCmpFall);

    void channelEnableOutput() const { hhrtim1.Instance->sCommonRegs.OENR |= this->HRTIM_OUTPUT_CHANNEL_IDENTIFIER; }

    void channelDisableOutput() const { hhrtim1.Instance->sCommonRegs.ODISR |= this->HRTIM_OUTPUT_CHANNEL_IDENTIFIER; }

    bool channelGetOutputEnabled() const
    {
        return (hhrtim1.Instance->sCommonRegs.OENR & this->HRTIM_OUTPUT_CHANNEL_IDENTIFIER) != 0;
    }

    void channelSetPWM(float duty)
    {
        assert_param(duty <= 1.0f);
        assert_param(duty >= 0.0f);

        *pRegCMPRise = (uint32_t)((1.0f - duty) * (HRTIM_PERIOD / 2));
        *pRegCMPFall = (uint32_t)((1.0f + duty) * (HRTIM_PERIOD / 2));
    }
};
