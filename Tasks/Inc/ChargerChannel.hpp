//
// Created by xiaol on 2025/3/20.
//

#pragma once

#include "main.h"
#include "hrtim.h"
#include "IncrementalPID.hpp"


class ChargerChannel {


public:

    static const uint32_t HRTIM_PERIOD = 27200;

    const uint32_t HRTIM_TIMERID;
    const uint32_t HRTIM_OUTPUT_CHANNEL_IDENTIFIER;

    volatile uint32_t *pRegCMPRise;
    volatile uint32_t *pRegCMPFall;

    enum ChannelState {
        OFF,
        IDLE,
        CHARGING_PRE,
        CHARGING_FAST,
        CHARGING_CV,
        ERROR_SHORT,
        ERROR_OVERVOLTAGE,
        ERROR_OVERCURRENT,
    };

    ChannelState state = OFF;

    IncrementalPID pidCurrent;

    void initChannel(volatile uint32_t *regCmpRise, volatile uint32_t *regCmpFall);

    void stateMachineTransition();

    void updateChannelStatus();

    void updateChannelPWM();

    void checkChannelError();

    ChargerChannel(uint32_t hrtimTimerid, uint32_t hrtimOutputChannelIdentifier, IncrementalPID pidCurrent) :
            HRTIM_TIMERID(hrtimTimerid), HRTIM_OUTPUT_CHANNEL_IDENTIFIER(hrtimOutputChannelIdentifier),
            pRegCMPRise(nullptr), pRegCMPFall(nullptr), pidCurrent(pidCurrent) {}


    void channelEnableOutput() const { hhrtim1.Instance->sCommonRegs.OENR |= this->HRTIM_OUTPUT_CHANNEL_IDENTIFIER; }

    void channelDisableOutput() const { hhrtim1.Instance->sCommonRegs.ODISR |= this->HRTIM_OUTPUT_CHANNEL_IDENTIFIER; }

    bool channelGetOutputEnabled() const {
        return (hhrtim1.Instance->sCommonRegs.OENR & this->HRTIM_OUTPUT_CHANNEL_IDENTIFIER) != 0;
    }


    void channelSetPWM(float duty) {
        assert_param(duty <= 1.0f);
        assert_param(duty >= 0.0f);

        *pRegCMPRise = (uint32_t) ((1.0f - duty) * (HRTIM_PERIOD / 2));
        *pRegCMPFall = (uint32_t) ((1.0f + duty) * (HRTIM_PERIOD / 2));
    }


};
