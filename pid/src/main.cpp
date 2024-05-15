#include <Arduino.h>
#include "PID.h"
#include "motor.cpp"
#include "mpu.cpp"

#define P 1
#define I 0
#define D 0

Motor motor = Motor();
Accelerometer accelerometer = Accelerometer();

int pidSource()
{
  return accelerometer.getAngle();
}

void pidOutput(int output)
{
  motor.setSpeed(output);
}

// P, I, and D represent constants in the user's program
PIDController myPIDController = PIDController<int>(P, I, D, pidSource, pidOutput);

void setup() {
  myPIDController.registerTimeFunction(millis);
}

void loop() {
  myPIDController.tick();
  delay(1);
}