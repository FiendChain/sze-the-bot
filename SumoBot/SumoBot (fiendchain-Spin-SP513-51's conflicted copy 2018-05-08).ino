#include <Bot.h>
#include <Constants.h>

Bot bot;
// left motor
const int LEFT_MOTOR_POWER = 10;
const int LEFT_MOTOR_FORWARD = 9;
const int LEFT_MOTOR_REVERSE = 8;
// right motor
const int RIGHT_MOTOR_POWER = 11;
const int RIGHT_MOTOR_FORWARD = 12;
const int RIGHT_MOTOR_REVERSE = 13;
// joystick
const int JOYSTICK_X = A0;
const int JOYSTICK_Y = A1;
// distance
const int LEFT_ECHO = 6;
const int LEFT_TRIGGER = 7;
const int RIGHT_ECHO = 3;
const int RIGHT_TRIGGER = 4;
// line
const int LINE = 5;

void setup() {
  Serial.begin(9600);
  delay(1000);
  // set controls
  bot.setLeftMotorPins(LEFT_MOTOR_POWER, LEFT_MOTOR_FORWARD, LEFT_MOTOR_REVERSE);
  bot.setRightMotorPins(RIGHT_MOTOR_POWER, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_REVERSE);
  // bot.setJoystickPins(JOYSTICK_X, JOYSTICK_Y);
  // set sensors
  bot.setLeftDistancePins(LEFT_ECHO, LEFT_TRIGGER);
  bot.setRightDistancePins(RIGHT_ECHO, RIGHT_TRIGGER);
  bot.setLinePin(LINE);
}

void loop() {
  update_ai();
  #ifdef DEBUGGING
  bot.debug();
  delay(1000);
  #else
  delay(10);
  #endif
}


