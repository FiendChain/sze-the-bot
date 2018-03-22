#include "Controls.h"
#include "Arduino.h"
#include "Constants.h"

Controls::Controls()
{
    
}

// float mapping
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

// motor controls
void Controls::setLeftMotorPins(int power, int forward, int reverse)
{
    leftMotor.setPins(power, forward, reverse);
}

void Controls::setRightMotorPins(int power, int forward, int reverse)
{
    rightMotor.setPins(power, forward, reverse);
}

void Controls::rotate(float angle, float magnitude)
{
    // constraining angle
    angle = constrain(angle, 0, 2*PI);
    int leftMotorValue = 0;
    int rightMotorValue = 0;
    // forward to right
    if(angle >= 0 && angle <= 0.5*PI) {
        leftMotorValue = MAX_PWM;
        rightMotorValue = mapfloat(angle, 0, 0.5*PI, MAX_PWM, -MAX_PWM);
    // right to reverse
    } else if(angle >= 0.5*PI && angle <= PI) {
        leftMotorValue = mapfloat(angle, 0.5*PI, PI, MAX_PWM, -MAX_PWM);
        rightMotorValue = -MAX_PWM;
    // reverse to left
    } else if(angle >= PI && angle <= 1.5*PI) {
        leftMotorValue = -MAX_PWM;
        rightMotorValue = mapfloat(angle, PI, 1.5*PI, -MAX_PWM, MAX_PWM);
    // left to forward
    } else {
        leftMotorValue = mapfloat(angle, 1.5*PI, 2*PI, -MAX_PWM, MAX_PWM);
        rightMotorValue = MAX_PWM;
    }
    // map magnitude of motors
    leftMotorValue *= magnitude/(float)MAX_PWM;
    rightMotorValue *= magnitude/(float)MAX_PWM;
    // write
    leftMotor.write(leftMotorValue);
    rightMotor.write(rightMotorValue);
}

// joystick controls
void Controls::setJoystickPins(int xPin, int yPin)
{
    joystick.setPins(xPin, yPin);
}

void Controls::readJoystick()
{
    float angle = joystick.getAngle();
    int magnitude = joystick.getMagnitude();
    rotate(angle, magnitude);
}

