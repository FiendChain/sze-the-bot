#include "Controls.h"
#include "Arduino.h"
#define UNKNOWN_PIN -1

Controls::Controls()
{
    // motors
    leftMotorPin = rightMotorPin = UNKNOWN_PIN;
}

// motor controls
void Controls::setMotorPins(int left, int right)
{
    leftMotorPin = left;
    rightMotorPin = right;
}

void Controls::writeMotor(int left, int right)
{
    if(leftMotorPin != UNKNOWN_PIN && rightMotorPin != UNKNOWN_PIN) {
        analogWrite(leftMotorPin, left);
        analogWrite(leftMotorPin, right);
    }
}

void Controls::rotate(Direction dir)
{
    switch(dir) {
    case LEFT:
        writeMotor(-255, 255);
        break;
    case RIGHT:
        writeMotor(255, -255);
        break;
    case FORWARD:
        writeMotor(255, 255);
        break;
    case BACKWARD:
        writeMotor(-255, -255);
        break;
    default:
        writeMotor(0, 0);
    }
}

