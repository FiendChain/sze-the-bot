#include "Joystick.h"
#include "Constants.h"
#include "Arduino.h"

JoystickController::JoystickController() {
    setPins(UNKNOWN_PIN, UNKNOWN_PIN);
}

JoystickController::JoystickController(int _xPin, int _yPin) {
    setPins(_xPin, _yPin);
}

// set pins for the jostick
// automatically set mode of pins to INPUT
// calibrate for unintended voltage drop by determining baseline, and the scale factor
// eg, if pin reads X, then max would be 2X. Then scale 0..X..2X to 0..127..255
void JoystickController::setPins(int _xPin, int _yPin) {
    xPin = _xPin;
    yPin = _yPin;
    // calibrate x
    if(xPin != UNKNOWN_PIN) {
        pinMode(xPin, INPUT);
        calibrateXPin(analogRead(xPin));
    } else {
        calibrateXPin(MAX_A_IN/2.0);
    }
    // calibrate y
    if(yPin != UNKNOWN_PIN) {
        pinMode(yPin, INPUT);
        calibrateYPin(analogRead(yPin));
    } else { 
        calibrateYPin(MAX_A_IN/2.0);
    }
}

// set the baseline and scale factor the the xpin
// consider MIN..CENTRE..MAX
// if it reads _xBaseline as X, then the range of the input would be 0..X..2X
// since we need to scale this to a better value for PWM, we need a scaling constant
// (0..X..2X) times xScale gives (0..MAX_PWM/2..MAX_PWM)
void JoystickController::calibrateXPin(int _xBaseline) {
    xBaseline = _xBaseline;
    xScale = MAX_PWM/(float)xBaseline;
}

// set the baseline and scale factor for the ypin
void JoystickController::calibrateYPin(int _yBaseline) {
    yBaseline = _yBaseline;
    yScale = MAX_PWM/(float)yBaseline;
}

// get the x value from 0..255(MAX_PWM)
int JoystickController::getX() {
    if(xPin != UNKNOWN_PIN) {
        int xValue = analogRead(xPin)-xBaseline;
        xValue *= xScale;
        xValue = constrain(xValue, -MAX_PWM, MAX_PWM);
        return xValue;
    }
    return 0;
}

// get the y value from 0..255(MAX_PWM)
int JoystickController::getY() {
    if(yPin != UNKNOWN_PIN) {
        int yValue = analogRead(yPin)-yBaseline;
        yValue *= yScale;
        yValue = constrain(yValue, -MAX_PWM, MAX_PWM);
        return yValue;
    }
    return 0;
}

// get the angle of the controller stick
// gives a floating point value from 0 to 2*PI
// North = 0, East = PI/2, South = PI, West = 1.5*PI, ~North = 2*PI
float JoystickController::getAngle() {
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

// get the magnitude of the joystick
// uses an approximation for faster reads
// returns value from 0..255(MAX_PWM)
int JoystickController::getMagnitude() {
    int xVal = getX();
    int yVal = getY();
    int magnitude = abs(xVal)+abs(yVal);
    magnitude = constrain(magnitude, MIN_PWM, MAX_PWM);
    return magnitude;
}
