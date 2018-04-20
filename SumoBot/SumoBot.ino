#include <Bot.h>
#include <Constants.h>

Bot bot;
// left motor
const int LEFT_MOTOR_POWER = 8;
const int LEFT_MOTOR_FORWARD = 9;
const int LEFT_MOTOR_REVERSE = 10;
// right motor
const int RIGHT_MOTOR_POWER = 11;
const int RIGHT_MOTOR_FORWARD = 12;
const int RIGHT_MOTOR_REVERSE = 13;
// joystick
const int JOYSTICK_X = A0;
const int JOYSTICK_Y = A1;

void setup()
{
  bot.getControls().setLeftMotorPins(LEFT_MOTOR_POWER, LEFT_MOTOR_FORWARD, LEFT_MOTOR_REVERSE);
  bot.getControls().setRightMotorPins(RIGHT_MOTOR_POWER, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_REVERSE);
  bot.getControls().setJoystickPins(JOYSTICK_X, JOYSTICK_Y);
  Serial.begin(9600);
}

void loop()
{
  bot.update();
  #ifdef DEBUGGING
  bot.debug();
  delay(1000);
  #else
  delay(1);
  #endif
}
