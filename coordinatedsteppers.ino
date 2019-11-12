
/**
   Purpose: Controll multiple stepper motors.

   @author: Wilson Tovar <twilson@uninorte.edu.co> github.com/krthr
   @version: 0.1.0 6/11/2019

   Every time measure is made using microseconds.
*/

#include "definitions.h"
#include "StepperMotor.h"

unsigned long current_micros = 0;
StepperMotor motors[3];

long long STEPS[][3]{
    {3200, 3200, 3200},
    {604, 8490, 8797},
    {10432, 9907, 739},
    {19962, 10487, 9448},
    {9530, 579, 8708},
    {7748, 12116, 19665},
    {13881, 5345, 4367},
    {43830, 19991, 23039},
    {14024, 7296, 9983},
    {21557, 3012, 16167}};

int DIR[][3]{
    {1, 1, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 0, 0},
    {0, 1, 1},
    {1, 1, 0},
    {1, 0, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 1, 1}};

int F[][3]{
    {400, 400, 400},
    {5825, 414, 400},
    {400, 421, 5646},
    {400, 761, 845},
    {400, 6583, 437},
    {1015, 649, 400},
    {400, 1038, 1271},
    {400, 876, 760},
    {400, 768, 561},
    {400, 2862, 533}

};

int POINTS = 9;
int actualPoint = 0;

void setup()
{

  Serial.begin(9600);

  Serial.println("Starting... \n");

  motors[0] = StepperMotor(0, P1, DIR1, ENABLE_PIN);
  motors[1] = StepperMotor(1, P2, DIR2, ENABLE_PIN);
  motors[2] = StepperMotor(2, P3, DIR3, ENABLE_PIN);

  /**
  motors[0].setDir(LOW);
  motors[0].setSteps(3200);
  motors[0].setInterval(400);
*/

  setAllMotors();

  Serial.println("Hi! Welcome  \nAll motors are ready.\n");
}

void loop()
{
  current_micros = micros();

  moveAllMotors();
  /**
  motors[0].nextStep(current_micros);
 */

  if (!motors[0].moving && !motors[1].moving && !motors[2].moving && actualPoint < 1)
  {
    Serial.println(actualPoint);
    setAllMotors();
  }
}

void moveAllMotors()
{
  motors[0].nextStep(current_micros);
  motors[1].nextStep(current_micros);
  motors[2].nextStep(current_micros);
}

/**
 * Set the information of all motors.
 */
void setAllMotors()
{
  setInfo(0);
  setInfo(1);
  setInfo(2);
  actualPoint++;
}

/**
 * Set the info of a motor.
 */
void setInfo(int motor)
{
  int i = motor - 1;
  motors[i].setSteps(STEPS[actualPoint][i]);
  motors[i].setDir(DIR[actualPoint][i]);
  motors[i].setInterval(F[actualPoint][i]);
}