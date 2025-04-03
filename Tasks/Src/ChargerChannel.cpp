//
// Created by xiaol on 2025/3/20.
//

#include "ChargerChannel.hpp"
#include "ChargerCommon.hpp"
#include "MathUtil.hpp"

void ChargerChannel::initChannel(volatile uint32_t *regCmpRise, volatile uint32_t *regCmpFall) {
    this->pRegCMPRise = regCmpRise;
    this->pRegCMPFall = regCmpFall;
}

void ChargerChannel::updateChannelStatus() {

}

void ChargerChannel::updateChannelDCDC() {
    if (this->state == IDLE) {
        tempDuty = this->voltageOut / ChargerCommon::voltageInput;
        tempDuty = M_CLAMP(tempDuty, 0.5f, 1.0f);
        this->channelSetPWM(0.1f);
        this->pidCurrent.update(0, this->currentOut);

    } else if (this->state == CHARGING) {
        this->pidCurrent.update(this->targetCurrent, this->currentOut);
        tempDuty += this->pidCurrent.getDeltaOutput();
        tempDuty = M_CLAMP(tempDuty, 0.5f, 0.9f);
        this->channelSetPWM(tempDuty);
    } else {
        this->channelDisableOutput();
    }
}

void ChargerChannel::updateChannelError() {

}
