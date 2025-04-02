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

void ChargerChannel::stateMachineTransition() {
    switch (this->state) {
        case STARTUP:
            /**
             * BEHAVIOR: Perform Hardware Check
             * TRANSITION: If Hardware Check is OK, transition to DETECTING. Else, transition to ERROR
             */
            break;


        case DETECTING:
            /**
             *
             * BEHAVIOR:
             *  Under DETECTING state, charger give 2% duty cycle.
             *  At DCM mode, small duty cycle is given so that output voltage is same as input voltage without load.
             *  This is used to trigger the battery that is not turned on.
             *
             * TRANSITION:
             *  If voltage is pulled under 15V, means shorted, transition to ERROR
             *  Else If current is larger than 0.5A or smaller than -0.3A, means overcurrent, transition to ERROR
             *  Else If voltage is larger than (input+0.5V), means overvoltage, transition to ERROR
             *  Else If voltage < 21V, transition to CHARGING_PRE
             *  Else If voltage < input-0.3V, transition to CHARGING_FAST
             *  Else Stay in DETECTING
             *  Can be manually triggered to CHARGING (By signal)
             */
            if (this->voltageOut < 15.0f) {
                this->state = ERROR_STATE;
            } else if (this->currentOut > 0.5f || this->currentOut < -0.3f) {
                this->state = ERROR_STATE;
            } else if (this->voltageOut > (ChargerCommon::voltageInput + 0.5f)) {
                this->state = ERROR_STATE;
            } else if (this->voltageOut < 21.0f) {
                this->state = CHARGING_PRE;
            } else if (this->voltageOut < ChargerCommon::voltageInput - 0.3f) {
                this->state = CHARGING_FAST;
            } else {
                this->state = DETECTING;
            }


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
        case ERROR_STATE:
            break;

    }
}
