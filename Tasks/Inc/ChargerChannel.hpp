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

    float GAIN_VOLTAGE_OUT;
    float BIAS_VOLTAGE_OUT;

    float GAIN_CURRENT_OUT;
    float BIAS_CURRENT_OUT;

    float voltageOut = 0.0f;
    float currentOut = 0.0f;

    bool errorOCFlag = false;
    bool errorShortFlag = false;
    bool errorOVFlag = false;
    bool errorSupplyFlag = false;

    enum ChannelState {
        STARTUP,
        DETECTING,
        CHARGING_PRE,
        CHARGING_FAST,
        ERROR_STATE
    };

    ChannelState state = STARTUP;

    IncrementalPID pidCurrent;

    void initChannel(volatile uint32_t *regCmpRise, volatile uint32_t *regCmpFall);

    void stateMachineTransition();

    void updateChannelStatus();

    void setVoltageDataRaw(uint16_t rawData) {
        this->voltageOut = this->GAIN_VOLTAGE_OUT * (float) rawData + this->BIAS_VOLTAGE_OUT;
    }

    void setCurrentDataRaw(uint16_t rawData) {
        this->currentOut = this->GAIN_CURRENT_OUT * (float) rawData + this->BIAS_CURRENT_OUT;
    }

    void updateChannelPWM();

    void checkChannelError();

    ChargerChannel(
            uint32_t hrtimTimerid, uint32_t hrtimOutputChannelIdentifier, IncrementalPID pidCurrent,
            float gainVoltageOut, float biasVoltageOut, float gainCurrentOut, float biasCurrentOut
    ) :
            HRTIM_TIMERID(hrtimTimerid), HRTIM_OUTPUT_CHANNEL_IDENTIFIER(hrtimOutputChannelIdentifier),
            pRegCMPRise(nullptr), pRegCMPFall(nullptr),
            GAIN_VOLTAGE_OUT(gainVoltageOut), BIAS_VOLTAGE_OUT(biasVoltageOut),
            GAIN_CURRENT_OUT(gainCurrentOut), BIAS_CURRENT_OUT(biasCurrentOut),
            pidCurrent(pidCurrent) {}


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
