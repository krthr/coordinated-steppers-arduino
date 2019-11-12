/**
 * StepperMotor.cpp
 * 
 * @author: Wilson Tovar <twilson@uninorte.edu.co> github.com/krthr
 * @version: 0.1.0 6/11/2019
 * 
 * Every time measure is made using microseconds.
 */

#include "Arduino.h"
#include "StepperMotor.h"
#include "definitions.h"

StepperMotor::StepperMotor(int id, int p_pin, int dir_pin, int en)
{
    this->id = id;
    this->_pulse_pin = p_pin;
    this->_dir_pin = dir_pin;
    this->_enable_pin = en;
    this->dir = LOW;
    this->interval = 400;

    this->moving = false;

    pinMode(_pulse_pin, OUTPUT);
    pinMode(_dir_pin, OUTPUT);
    pinMode(_enable_pin, OUTPUT);

    digitalWrite(_enable_pin, HIGH);
    digitalWrite(_dir_pin, LOW);
}

/**
 * Move the motor
 */
void StepperMotor::nextStep(unsigned long current_micros)
{
    if (this->actual_steps < this->total_steps)
    {
        if (current_micros - this->last_micros >= this->interval) // the elapsed time is enought
        {
            this->moving = true;
            int newState = this->state == LOW ? HIGH : LOW;
            digitalWrite(this->_pulse_pin, newState);
            digitalWrite(this->_dir_pin, this->dir);
            this->state = newState;
            this->actual_steps++;
            this->last_micros = current_micros;
        }
    }
    else
        this->stopMotor();
}

void StepperMotor::nextStep()
{
    unsigned long current_micros = micros();
    this->nextStep(current_micros);
}

void StepperMotor::resetSteps()
{
    this->setSteps(0);
}

void StepperMotor::setDir(int dir)
{
    this->dir = dir == 0 ? 1 : 0;
    digitalWrite(_dir_pin, dir);
}

void StepperMotor::setSteps(long long steps)
{
    this->total_steps = steps;
    this->actual_steps = 0;
}

void StepperMotor::setInterval(unsigned long interval)
{
    this->interval = interval;
}

void StepperMotor::stopMotor()
{
    this->moving = false;
    this->total_steps = 0;
    this->actual_steps = 0;

    //Serial.print("m");
    //Serial.println(this->id + " -> stopped.");
}
