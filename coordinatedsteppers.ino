/**
 * Purpose: Controll multiple stepper motors.
 * 
 * @author: Wilson Tovar <twilson@uninorte.edu.co> github.com/krthr
 * @version: 0.1.0 6/11/2019
 * 
 * Every time measure is made using microseconds.
 */

#define ENABLE_PIN  12
#define P1      9
#define P2      6
#define P3      4
#define DIR1    10
#define DIR2    7
#define DIR3    5

#define INPUT_SIZE 30

#include "StepperMotor.h"

unsigned long current_micros = 0;
StepperMotor motors[3];

void setup() 
{
  Serial.begin(9600); 

  motors[0] = StepperMotor(P1, DIR1, ENABLE_PIN);
  motors[1] = StepperMotor(P2, DIR2, ENABLE_PIN);
  motors[2] = StepperMotor(P3, DIR3, ENABLE_PIN);

  for (int i = 0; i < 3; i++)
  {
    motors[i].setSteps(3200);
  }
}

void loop() 
{
  current_micros = micros(); 

  for (int i = 0; i < 3; i++)
  {
    motors[i].nextStep(current_micros);
  }
}
