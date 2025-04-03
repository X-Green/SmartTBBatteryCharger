//
// Created by xiaol on 2025/3/20.
//

#include "ChargerChannel.hpp"
#include "ChargerCommon.hpp"

void ChargerChannel::initChannel(volatile uint32_t *regCmpRise, volatile uint32_t *regCmpFall) {
    this->pRegCMPRise = regCmpRise;
    this->pRegCMPFall = regCmpFall;
}

void ChargerChannel::updateChannelStatus() {

}

void ChargerChannel::updateChannelPWM() {

}

void ChargerChannel::checkChannelError() {

}
