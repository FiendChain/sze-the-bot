#include <Bot.h>

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
// distance
const int ECHO = 6;
const int TRIGGER = 7;
// line
const int LINE = 5;

void setup() {
  // set controls
  bot.setLeftMotorPins(LEFT_MOTOR_POWER, LEFT_MOTOR_FORWARD, LEFT_MOTOR_REVERSE);
  bot.setRightMotorPins(RIGHT_MOTOR_POWER, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_REVERSE);
  bot.setJoystickPins(JOYSTICK_X, JOYSTICK_Y);
  // set sensors
  bot.setDistancePins(ECHO, TRIGGER);
  bot.setLinePin(LINE);
  Serial.begin(9600);
}

void loop() {
  bot.update();
  #ifdef DEBUGGING
  bot.debug();
  delay(1000);
  #else
  delay(1);
  #endif
}
