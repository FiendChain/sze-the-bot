#include "Controls.h"
#include "Arduino.h"
#include "Constants.h"

Controls::Controls() {
    
}

// float mapping
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

// set the left motor pins
void Controls::setLeftMotorPins(int power, int forward, int reverse) {
    leftMotor.setPins(power, forward, reverse);
}

// set the right motor pins
void Controls::setRightMotorPins(int power, int forward, int reverse) {
    rightMotor.setPins(power, forward, reverse);
}

// move the bot in four axises, and stop
// forward, backward, left, right, stop
// uses the <Movement> enumeration in Controls.h
void Controls::move(Movement move) {
    int leftMotorValue = MIN_PWM;
    int rightMotorValue = MIN_PWM;
    // get the movement type
    switch(move) {
    case FORWARD: 
        leftMotorValue = MAX_PWM;
        rightMotorValue = MAX_PWM;
        break;
    case BACKWARD:
        leftMotorValue = -MAX_PWM;
        rightMotorValue = -MAX_PWM;
        break;
    case LEFT:
        leftMotorValue = -MAX_PWM;
        rightMotorValue = MAX_PWM;
        break;
    case RIGHT:
        leftMotorValue = MAX_PWM;
        rightMotorValue = -MAX_PWM;
        break;
    case STOP:
        leftMotorValue = MIN_PWM;
        rightMotorValue = MIN_PWM;
        break;
    }
    leftMotor.write(leftMotorValue);
    rightMotor.write(rightMotorValue);
}

// move the bot in an analog fashion
// angle specifies the direction in which the bot moves
// angle goes from 0 to 2*PI
// magnitude specifies how fast to move in that direction
// magnitude goes from 0(MIN_PWM) to 255(MAX_PWM)
// consider the angle and magnitude parameters as a vector, which determines the direction of the bot
void Controls::rotate(float angle, float magnitude) {
    // constraining angle
    angle = constrain(angle, 0, 2*PI);
    magnitude = constrain(magnitude, MIN_PWM, MAX_PWM);
    int leftMotorValue = MIN_PWM;
    int rightMotorValue = MIN_PWM;
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

// set joystick pins
void Controls::setJoystickPins(int xPin, int yPin) {
    joystick.setPins(xPin, yPin);
}

// control the bot using the joystick controls
void Controls::readJoystick() {
    float angle = joystick.getAngle();
    int magnitude = joystick.getMagnitude();
    rotate(angle, magnitude);
}

