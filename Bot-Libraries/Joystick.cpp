#include "Joystick.h"
#include "Constants.h"
#include "Arduino.h"

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
    if(xPin != UNKNOWN_PIN)
        calibrateXPin(analogRead(xPin));
    else 
        calibrateXPin(MAX_A_IN/2);
    // calibrate y
    if(yPin != UNKNOWN_PIN)
        calibrateYPin(analogRead(yPin));
    else 
        calibrateYPin(MAX_A_IN/2);
}

void JoystickController::calibrateXPin(int _xBaseline)
{
    xBaseline = _xBaseline;
    xScale = MAX_PWM/(float)_xBaseline;
}

void JoystickController::calibrateYPin(int _yBaseline)
{
    yBaseline = _yBaseline;
    yScale = MAX_PWM/(float)_yBaseline;
}

int JoystickController::getX()
{
    if(xPin != UNKNOWN_PIN) {
        int xValue = analogRead(xPin)-xBaseline;
        xValue *= xScale;
        xValue = constrain(xValue, -MAX_PWM, MAX_PWM);
        return xValue;
    }
    return 0;
}

int JoystickController::getY()
{
    if(yPin != UNKNOWN_PIN) {
        int yValue = analogRead(yPin)-yBaseline;
        yValue *= yScale;
        yValue = constrain(yValue, -MAX_PWM, MAX_PWM);
        return yValue;
    }
    return 0;
}

float JoystickController::getAngle()
{
    float angle = 0; 
    int xVal = getX();
    int yVal = getY();
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
    return angle;
}

int JoystickController::getMagnitude()
{
    int xVal = getX();
    int yVal = getY();
    int magnitude = abs(xVal)+abs(yVal);
    magnitude = constrain(magnitude, 0 , MAX_PWM);
    return magnitude;
}
