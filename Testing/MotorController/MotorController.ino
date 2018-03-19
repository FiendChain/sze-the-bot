#include <Motor.h>
#include <Constants.h>
#include <Joystick.h>
#include <stdio.h>

MotorController motor;
const int POWER_PIN = 11;
const int FORWARD_PIN = 12;
const int REVERSE_PIN = 13;

// controller
JoystickController joystick;
const int CONTROLLER_X = A0;
const int CONTROLLER_Y = A1;


void setup()
{
  motor = MotorController(POWER_PIN, FORWARD_PIN, REVERSE_PIN);
  joystick = JoystickController(CONTROLLER_X, CONTROLLER_Y);
  Serial.begin(9600);
}

void loop()
{
 // test_cycle();
 test_controller();
}

// go through all power levels
void test_cycle()
{
  for(int power = MAX_PWM; power >= -MAX_PWM; power -= 5) {
    motor.write(power);
    delay(20);
  }
}

// test using controller
void test_controller()
{
  int value = joystick.getX();
  char buffer[100] = {0};
  snprintf(buffer, 100, "<controller %p> read: %d, actual: %d", motor, value, analogRead(CONTROLLER_X));
  motor.write(value);
  Serial.println(buffer);
  delay(10);
}




