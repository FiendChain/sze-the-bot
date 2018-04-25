#include <Bot.h>
#include <Controls.h>
#include <Constants.h>
#include <Sensors.h>

Bot bot;
Controls controls = bot.getControls();  // fetch control handler from bot to configure pin setup
Sensors sensors = bot.getSensors();
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

void setup() {
  // set controls
  controls.setLeftMotorPins(LEFT_MOTOR_POWER, LEFT_MOTOR_FORWARD, LEFT_MOTOR_REVERSE);
  controls.setRightMotorPins(RIGHT_MOTOR_POWER, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_REVERSE);
  controls.setJoystickPins(JOYSTICK_X, JOYSTICK_Y);
  // set sensors
  
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
