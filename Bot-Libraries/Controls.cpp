#include "Controls.h"
#include "Arduino.h"
#include "Constants.h"

Controls::Controls()
:   leftMotor(MotorController()),   // motors
    rightMotor(MotorController()),
    joystick(JoystickController())
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
    leftMotorValue *= magnitude/(float)MAX_PWM;
    rightMotorValue *= magnitude/(float)MAX_PWM;
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
    // get cartesian components of joystick
    int xVal = joystick.getX();
    int yVal = joystick.getY();
    // get magnitude of joystick
    int magnitude = abs(xVal)+abs(yVal);
    magnitude = constrain(magnitude, 0 , MAX_PWM);
    // get angle
    float angle = 0; 
    // all directions except 0, PI/2, PI, 1.5PI
    if(yVal != 0 && xVal != 0) {
        float absRatio = abs(xVal)/(float)abs(yVal);
        float absAngle = atan(absRatio);
        // top right
        if(yVal > 0 && xVal > 0)
            angle = absAngle;
        // bottom right
        else if(yVal < 0 && xVal > 0)
            angle = PI - absAngle;
        // bottom left
        else if(yVal < 0 && xVal < 0)
            angle = PI + absAngle;
        // top left
        else if(yVal > 0 && xVal < 0)
            angle = 2*PI - absAngle;
    // forward and back
    } else if(yVal != 0) {
        angle = (yVal > 0) ? 0 : PI;
    // left and right
    } else if(xVal != 0) {
        angle = (xVal > 0) ? 0.5*PI : 1.5*PI;
    // no input
    } else {
        angle = 0;
    }
    rotate(angle, magnitude);
    
}

// debugging
void Controls::debug()
{
    joystick.debug();
}

