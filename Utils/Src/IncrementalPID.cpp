#include "IncrementalPID.hpp"

#include "Config.hpp"

IncrementalPID::IncrementalPID(float kPOnTarget, float kPOnMeasurement, float kI, float kD)
    : kPOnTarget(kPOnTarget),
      kPOnMeasurement(kPOnMeasurement),
      kI(kI),
      kD(kD),
      lastMeasurement(0.0f),
      lastLastMeasurement(0.0f),
      lastTarget(0.0f),
      deltaOutput(0.0f),
      multiplicationParameter({0, 0, 0, 0, 0})
{
    configASSERT(this->kPOnTarget >= 0.0f);
    configASSERT(this->kPOnMeasurement >= 0.0f);
    configASSERT(this->kI >= 0.0f);
    configASSERT(this->kD >= 0.0f);

    this->multiplicationParameter.paramTarget              = this->kPOnTarget + this->kI;
    this->multiplicationParameter.paramMeasurement         = this->kPOnMeasurement - this->kI + this->kD;
    this->multiplicationParameter.paramLastTarget          = -this->kPOnTarget;
    this->multiplicationParameter.paramLastMeasurement     = -this->kPOnMeasurement - 2.0f * this->kD;
    this->multiplicationParameter.paramLastLastMeasurement = this->kD;
}

void IncrementalPID::update(float target, float measurement)
{
    this->deltaOutput = this->kPOnTarget * (target - this->lastTarget) -
                        this->kPOnMeasurement * (measurement - this->lastMeasurement) +
                        this->kI * (target - measurement) +
                        this->kD * (measurement - 2.0f * this->lastMeasurement + this->lastLastMeasurement);

    this->lastTarget          = target;
    this->lastLastMeasurement = this->lastMeasurement;
    this->lastMeasurement     = measurement;
}

void IncrementalPID::updateDataNoOutput(float target, float measurement)
{
    this->lastTarget          = target;
    this->lastLastMeasurement = this->lastMeasurement;
    this->lastMeasurement     = measurement;
}

float IncrementalPID::getDeltaOutput() const { return this->deltaOutput; }

float IncrementalPID::getDeltaI() const { return this->kI * (this->lastTarget - this->lastMeasurement); }

void IncrementalPID::reset()
{
    this->lastTarget      = 0.0f;
    this->lastMeasurement = 0.0f;
    this->deltaOutput     = 0.0f;
}
