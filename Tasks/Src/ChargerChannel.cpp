//
// Created by xiaol on 2025/3/20.
//

#include "ChargerChannel.hpp"

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

void ChargerChannel::stateMachineTransition() {
    switch (this->state) {
        case OFF:
            // Just Disable output
            break;


        case IDLE:
            /**
             *
             * BEHAVIOR:
             *  Under IDLE state, charger give a small pwm duty cycle.
             *  At DCM mode, small duty cycle is given so that output voltage is same as input voltage without load.
             *  This is used to trigger the battery that is not turned on.
             *
             * TRANSITION:
             *  1. If voltage is pulled to 15V~(input-0.3V), means battery is detected, transition to CHARGING
             *  2. If voltage is pulled under 15V, means shorted, transition to ERROR_SHORT
             *  3. If current is larger than 0.5A, means overcurrent, transition to ERROR_OVERCURRENT
             *  4. If voltage is larger than (input+0.5V), means overvoltage, transition to ERROR_OVERVOLTAGE
             *  5. Can be manually triggered to CHARGING
             */

            break;

        case CHARGING_PRE:
            break;
        case CHARGING_CV:
            break;
        case CHARGING_FAST:
            /**
             *
             * BEHAVIOR:
             *  Under CHARGING state, pidCurrent will be used to control the charging current.
             *
             * TRANSITION:
             *  1. If current is larger than 6A, means overcurrent, transition to ERROR_OVERCURRENT
             *  2. If (current < 0.2A) && (voltage > input-0.3V), means battery is full, transition to IDLE
             *  3. If (current < 0.2A) && (voltage < input-0.3V), means buck is not working, transition to ERROR_BUCK
             *  4. If ()
             */

            break;
        case ERROR_SHORT:
            break;
        case ERROR_OVERVOLTAGE:
            break;
        case ERROR_OVERCURRENT:
            break;

    }
}
