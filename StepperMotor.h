#ifndef StepperMotor_h
#define StepperMotor_h

#include "Arduino.h"

class StepperMotor
{
public:
    StepperMotor(int p, int dir, int en);
    StepperMotor() = default;

    int dir;
    int total_steps;
    int actual_steps;
    int interval;
    int state;

    void nextStep(unsigned long current_micros);
    void resetSteps();

    void setSteps(int steps);
    void setDir(int dir);

private:
    unsigned long last_micros;
    int _pulse_pin;
    int _dir_pin;
    int _enable_pin;
};

#endif