//
// Created by xiaol on 2025/3/20.
//

#include "ChargerChannel.hpp"

#include "MathUtil.hpp"
#include "SampleTask.hpp"

void ChargerChannel::initChannel(volatile uint32_t *regCmpRise, volatile uint32_t *regCmpFall)
{
    this->pRegCMPRise = regCmpRise;
    this->pRegCMPFall = regCmpFall;
}

void ChargerChannel::updateChannelStatus() {}

void ChargerChannel::updateChannelDCDC()
{
    if (this->state == IDLE)
    {
        tempDuty = *(this->pVoltageOut) / Tasks::SampleTask::voltageIn;
        tempDuty = M_CLAMP(tempDuty, 0.2f, 0.87f);
        this->channelSetPWM(0.1f);
        this->pidCurrent.update(0, *this->pCurrentOut);
        this->pidVoltage.update(this->targetVoltage, *this->pVoltageOut);
    }
    else if (this->state == CHARGING)
    {
        this->pidCurrent.update(this->targetCurrent, *this->pCurrentOut);
        this->pidVoltage.update(this->targetVoltage, *this->pVoltageOut);
        // choose the smaller delta_output to avoid overvoltage or overcurrent
        float vOutDuty = tempDuty + this->pidVoltage.getDeltaOutput() / Tasks::SampleTask::voltageIn;
        float iOutDuty = tempDuty + this->pidCurrent.getDeltaOutput();

        if ((*this->pVoltageOut > 0.8f * this->targetVoltage) && (vOutDuty < iOutDuty))
        {
            tempDuty = vOutDuty;
        }
        else
        {
            tempDuty = iOutDuty;
        }
        //        if (*this->pCurrentOut < 0.3f)
        //        {
        //            tempDuty = M_CLAMP(tempDuty, 0.2f, 0.87f);
        //        }
        //        else
        //        {
        tempDuty = M_CLAMP(tempDuty, 0.2f, 0.97f);
        //        }
        this->channelSetPWM(tempDuty);
    }
    else
    {
        this->channelDisableOutput();
        this->pidCurrent.updateDataNoOutput(0, *this->pCurrentOut);
        this->pidVoltage.updateDataNoOutput(this->targetVoltage, *this->pVoltageOut);
    }
    //    this->pidCurrent.update(this->targetCurrent, *this->pCurrentOut);
    //    tempDuty = M_CLAMP(tempDuty, 0.5f, 0.9f);
}

void ChargerChannel::updateChannelError() {}
