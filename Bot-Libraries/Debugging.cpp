#include "Arduino.h"
#include "Bot.h"
#include "Constants.h"
#include "Controls.h"
#include "Joystick.h"
#include "Motor.h" 

#ifdef DEBUGGING
#include <stdio.h>      // used for making debug strings
#include "freeMemory.h" // used for checking total free memory

// debug bot
void Bot::debug()
{
    char buffer[MAX_BUFFER] = {0};
    snprintf(buffer, MAX_BUFFER, "<< Debugging Bot at %p", this);
    Serial.println(buffer);
    controls.debug();
    snprintf(buffer, MAX_BUFFER, "Total free memory: %u bytes\n", freeMemory());
    Serial.println(buffer);
}

// debug controls
void Controls::debug()
{
    joystick.debug();
    leftMotor.debug();
    rightMotor.debug();
}

// debug joystick
void JoystickController::debug()
{
    char buffer[MAX_BUFFER] = {0};
    snprintf(buffer, MAX_BUFFER, "<JoystickController at %p>\n", this);
    Serial.print(buffer);
    //snprintf(buffer, MAX_BUFFER, "xPin:%d xMid:%d xVal:%d\n", xPin, xBaseline, getX());
    snprintf(buffer, MAX_BUFFER, "xPin: %d, xScale: %f, xBaseline: %d, xVal: %d\n", xPin, xScale, xBaseline, getX());
    Serial.print(buffer);
    //snprintf(buffer, MAX_BUFFER, "yPin:%d yMid:%d yVal:%d\n", yPin ,yBaseline, getY());
    snprintf(buffer, MAX_BUFFER, "yPin: %d, yScale: %f, yBaseline: %d, yVal: %d\n", yPin, yScale, yBaseline, getY());
    Serial.print(buffer);
}

// debug motor
void MotorController::debug()
{
    char buffer[MAX_BUFFER] = {0};
    snprintf(buffer, MAX_BUFFER, "<MotorController at %p>\n", this);
    Serial.print(buffer);
    snprintf(buffer, MAX_BUFFER, "powerPin:%d forwardPin:%d reversePin:%d\n", powerPin, forwardPin, reversePin);
    Serial.print(buffer);
    snprintf(buffer, MAX_BUFFER, "powerVal:%d forwardVal:%d reverseVal:%d\n", powerValue, forwardValue, reverseValue);
    Serial.print(buffer);
}
#else
// dont do anything
void Bot::debug() {}
void Controls::debug() {}
void JoystickController::debug() {}
void MotorController::debug() {}
#endif