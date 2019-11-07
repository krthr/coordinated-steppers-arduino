#include "Arduino.h"
#include "StepperMotor.h"

StepperMotor::StepperMotor(int p, int dir, int en)
{
    this->_pulse_pin = p;
    this->_dir_pin = dir;
    this->_enable_pin = en;

    pinMode(_pulse_pin, OUTPUT);
    pinMode(_dir_pin, OUTPUT);
    pinMode(_enable_pin, OUTPUT);

    digitalWrite(_enable_pin, HIGH);
}

/**
 * Move the motor
 */
void StepperMotor::nextStep(unsigned long current_micros)
{
    if (this->actual_steps >= this->total_steps)
    {
        this->resetSteps();
        return;
    }

    // the elapsed time is not enought
    if (current_micros - this->last_micros < this->interval)
    {
        return;
    }

    int newState = this->state == LOW ? HIGH : LOW;
    digitalWrite(this->_pulse_pin, newState);
    this->state = newState;
    this->actual_steps++;
    this->last_micros = current_micros;
}

void StepperMotor::resetSteps()
{
    this->setSteps(0);
}

void StepperMotor::setDir(int dir)
{
    this->dir = dir;
    digitalWrite(_dir_pin, dir);
}

void StepperMotor::setSteps(int steps)
{
    this->total_steps = steps;
    this->actual_steps = 0;
}
