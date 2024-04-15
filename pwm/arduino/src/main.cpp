#include <Arduino.h>
#include "joink.h"

int MOTOR_PIN = PB_4;
int TRIGGER_PIN = PA_9;

int triggerRisingEdge = 0;
int lastStatusTrigger = 0;

bool started = false;
bool reversed = false;

PWM motor;

float motor_pwm = 125;

bool PinStateChanged(int pin, int *lastButtonState, int *buttonRisingEdge)
{
  // Get pin state
  int buttonState = digitalRead(pin);

  // Here starts the code for detecting an edge
  if (buttonState != *lastButtonState)
  {
    if (buttonState == LOW)
    {
      *buttonRisingEdge = 0;
    }
    else
    {
      *buttonRisingEdge = 1;
    }
    *lastButtonState = buttonState;
    return true;
  }

  return false;
}

void updateStatus()
{
  if (PinStateChanged(TRIGGER_PIN, &lastStatusTrigger, &triggerRisingEdge))
  {
    if (triggerRisingEdge == 1)
    {
      if (started)
      {
        // Stopping the motor
        Serial.println("Stopping motor");
        started = false;

        // Reset motor PWM
        motor_pwm = motor.get_min_us();
      }
      else
      {
        // Starting the motor
        Serial.println("Starting motor");
        started = true;

        motor_pwm = motor.get_min_us();
      }
    }
  }
}

void checkForStop() {
  if(Serial.available() == 0) {
    return;
  }

  started = false;
}

void setup()
{
  motor.begin(MOTOR_PIN, 2000, 125, 250); // pin 1 (slice 0): Oneshot motor ESC 2000Hz pulse 125-250 us

  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop()
{
  updateStatus();
  checkForStop();

  if (!started)
    return;

  if(!reversed) {
    motor_pwm += 0.01;
  }
  else{
    motor_pwm -= 0.10;
  }

  Serial.println(motor_pwm);
  if (!reversed && motor_pwm > motor.get_max_us())
  {
    reversed = true;
  }

  if(reversed && motor_pwm < motor.get_min_us()) {
    reversed = false;
  }

  motor.writeMicroseconds(motor_pwm);

  delay(2);
}