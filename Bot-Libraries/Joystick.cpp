#include "Joystick.h"
#include "Constants.h"
#include "Arduino.h"
#include <stdio.h>

JoystickController::JoystickController()
{
    setPins(UNKNOWN_PIN, UNKNOWN_PIN);
}

JoystickController::JoystickController(int _xPin, int _yPin)
{
    setPins(_xPin, _yPin);
}

void JoystickController::setPins(int _xPin, int _yPin)
{
    pinMode(_xPin, INPUT);
    pinMode(_yPin, INPUT);
    xPin = _xPin;
    yPin = _yPin;
    // calibrate x
    if(xPin != UNKNOWN_PIN) {
        calibrateXPin(analogRead(xPin));
    } else {
        calibrateXPin(MAX_A_IN/2);
    }
    // calibrate y
    if(yPin != UNKNOWN_PIN) {
        calibrateYPin(analogRead(yPin));
    } else {
        calibrateYPin(MAX_A_IN/2);
    }
}

void JoystickController::calibrateXPin(int _xBaseline)
{
    xBaseline = _xBaseline;
    // convert 0...1024-xBaseline to 0...255 
    xScalePositive = MAX_PWM/float(MAX_A_IN-xBaseline);
    // convert -xBaseline...0 to -255...0
    xScaleNegative = MAX_PWM/float(xBaseline);
}

void JoystickController::calibrateYPin(int _yBaseline)
{
    yBaseline = _yBaseline;
    // convert 0...1024-xBaseline to 0...255 
    yScalePositive = MAX_PWM/float(MAX_A_IN-yBaseline);
    // convert -xBaseline...0 to -255...0
    yScaleNegative = MAX_PWM/float(yBaseline);
}

int JoystickController::getX()
{
    if(xPin != UNKNOWN_PIN) {
        int xValue = analogRead(xPin);
        // map 0...1024 to -255...255
        xValue -= xBaseline;    
        if(xValue < 0) {
            xValue *= xScaleNegative;
        } else if(xValue > 0) {
            xValue *= xScalePositive;
        }
        return xValue;
    }
    return 0;
}

int JoystickController::getY()
{
    if(yPin != UNKNOWN_PIN) {
        int yValue = analogRead(yPin);
        // map 0...1024 to -255...255
        yValue -= yBaseline;    
        if(yValue < 0) {
            yValue *= yScaleNegative;
        } else if(yValue > 0) {
            yValue *= yScalePositive;
        }
        return -yValue; // y axis is inverted
    }
    return 0;
}

void JoystickController::debug()
{
    char buffer[100] = {0};
    snprintf(buffer, 100, "<JoystickController %p> \nxPin:%d xMid:%d xVal:%d \nyPin:%d yMid:%d yVal:%d", this, xPin, xBaseline, getX(), yPin ,yBaseline, getY());
    Serial.println(buffer);
}