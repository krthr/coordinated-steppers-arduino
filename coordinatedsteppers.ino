/**
   Purpose: Controll multiple stepper motors.

   @author: Wilson Tovar <twilson@uninorte.edu.co> github.com/krthr
   @version: 0.1.0 6/11/2019

   Every time measure is made using microseconds.
*/

#define ENABLE_PIN 12
#define P1 9
#define P2 6
#define P3 4
#define DIR1 10
#define DIR2 7
#define DIR3 5
#define INPUT_SIZE 30
#define ld long double
#define ul unsigned long

#include "StepperMotor.h"

const ld R = 1;
ul current_micros = 0;
StepperMotor motors[3];

char input[INPUT_SIZE + 1];

void setup()
{
  Serial.begin(9600);

  motors[0] = StepperMotor(P1, DIR1, ENABLE_PIN);
  motors[1] = StepperMotor(P2, DIR2, ENABLE_PIN);
  motors[2] = StepperMotor(P3, DIR3, ENABLE_PIN);

  motors[0].setSteps(13200);
  motors[1].setSteps(4200);
  motors[2].setSteps(8200);

  motors[0].setInterval(400);
  motors[1].setInterval(400);
  motors[2].setInterval(400);

  //motors[2].setDir(HIGH);
  //motors[0].setDir(HIGH);
  //motors[1].setDir(HIGH);
}

void loop()
{

  current_micros = micros();

  handleSerial();

  for (int i = 0; i < 3; i++)
  {
    motors[i].nextStep(current_micros);
  }
}

void handleSerial()
{
  while (Serial.available() > 0)
  {
    char c = Serial.read();

    switch (c)
    {
    case 's':
    {
      // stop all: s
      stopAll();
      break;
    }
    }
  }
}

void stopAll()
{
  Serial.println("Stoping all motors.");
  for (int i = 0; i < 3; i++)
  {
    motors[i].stopMotor();
  }
}

ld l1(ld x, ld y, ld z)
{
  return sqrt(
      pow(x, 2) + pow(y - R, 2) + pow(z, 2));
}

ld l2(ld x, ld y, ld z)
{
  ld a = x - ((sqrt(3) / 2) * R);
  ld b = y + (0.5 * R);

  return sqrt(
      pow(a, 2) + pow(b, 2) + pow(z, 2));
}

ld l3(ld x, ld y, ld z)
{
  ld a = x + (sqrt(3) / 2) * R;
  ld b = y + (0.5 * R);

  return sqrt(
      pow(a, 2) + pow(b, 2) + pow(z, 2));
}
