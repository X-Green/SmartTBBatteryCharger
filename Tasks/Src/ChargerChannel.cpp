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
             *  If input voltage not within 26V to 26.3V, transition to ERROR
             *  Else If voltage is pulled under 15V, means shorted, transition to ERROR
             *  Else If current is larger than 0.5A or smaller than -0.3A, means overcurrent, transition to ERROR
             *  Else If voltage is larger than (input+0.5V), means overvoltage, transition to ERROR
             *  Else If voltage < 21V, transition to CHARGING_PRE
             *  Else If voltage < input-0.3V, transition to CHARGING_FAST
             *  Else Stay in DETECTING
             *  Can be manually triggered to CHARGING (By signal)
             */

            if (ChargerCommon::voltageInput > 26.3f || ChargerCommon::voltageInput < 26.0f) {
                this->state = ERROR_STATE;
                this->errorSupplyFlag = true;
            } else if (this->voltageOut < 15.0f) {
                this->state = ERROR_STATE;
                this->errorShortFlag = true;
            } else if (this->currentOut > 0.5f || this->currentOut < -0.3f) {
                this->state = ERROR_STATE;
                this->errorOCFlag = true;
            } else if (this->voltageOut > (ChargerCommon::voltageInput + 0.5f)) {
                this->state = ERROR_STATE;
                this->errorOVFlag = true;
            } else if (this->voltageOut < 21.0f) {
                this->state = CHARGING_PRE;
            } else if (this->voltageOut < ChargerCommon::voltageInput - 0.3f) {
                this->state = CHARGING_FAST;
            } else {
                this->state = DETECTING;
            }
            break;

        case CHARGING_PRE:
            /**
             * BEHAVIOR:
             *  Pre-charge the battery to 21V. Charging current is limited to max 0.5A.
             *  Use PID for current control.
             *
             * TRANSITION:
             *  If input voltage not within 26V to 26.3V, transition to ERROR
             *  Else If voltage is pulled under 15V, means shorted, transition to ERROR
             *  Else If current is larger than 0.8A or smaller than -0.2A, means overcurrent, transition to ERROR
             *  Else If voltage is larger than (input+0.3V), means overvoltage, transition to ERROR
             *  Else If voltage > 21 , goto fast charge
             *  Else stay in CHARGING_PRE
             */
            if (ChargerCommon::voltageInput > 26.3f || ChargerCommon::voltageInput < 26.0f) {
                this->state = ERROR_STATE;
                this->errorSupplyFlag = true;
            } else if (this->voltageOut < 15.0f) {
                this->state = ERROR_STATE;
                this->errorShortFlag = true;
            } else if (this->currentOut > 0.8f || this->currentOut < -0.2f) {
                this->state = ERROR_STATE;
                this->errorOCFlag = true;
            } else if (this->voltageOut > (ChargerCommon::voltageInput + 0.3f)) {
                this->state = ERROR_STATE;
                this->errorOVFlag = true;
            } else if (this->voltageOut > 21.0f) {
                this->state = CHARGING_FAST;
            } else {
                this->state = CHARGING_PRE;
            }

            break;
        case CHARGING_FAST:
            /**
             *
             * BEHAVIOR:
             *  Under CHARGING state, max current is 4A.
             *
             * TRANSITION:
             *  If input voltage not within 26V to 26.3V, transition to ERROR
             *  Else If voltage is pulled under 15V, means shorted, transition to ERROR
             *  Else If current is larger than 6A or smaller than -0.2A, means overcurrent, transition to ERROR
             *  Else If voltage is larger than (input+0.3V), means overvoltage, transition to ERROR
             *
             */

            break;
        case ERROR_STATE:
            break;

    }
}
