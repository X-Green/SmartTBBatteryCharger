#pragma once

class IncrementalPID {
public:
    IncrementalPID(float kPOnTarget, float kPOnMeasurement, float kI, float kD);

    void update(float target, float measurement);

    void updateDataNoOutput(float target, float measurement);

    float getDeltaOutput() const;

    float getDeltaI() const;

    void reset();

private:
    float kPOnTarget;
    float kPOnMeasurement;
    float kI;
    float kD;

    float lastMeasurement;
    float lastLastMeasurement;
    float lastTarget;
    float deltaOutput;

    struct MultiplicationParameter {
        float paramTarget;
        float paramLastTarget;
        float paramMeasurement;
        float paramLastMeasurement;
        float paramLastLastMeasurement;
    };

    MultiplicationParameter multiplicationParameter;
};