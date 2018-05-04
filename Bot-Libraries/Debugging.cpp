#include "Arduino.h"
#include "Bot.h"
#include "Constants.h"
#include "Joystick.h"
#include "Motor.h" 
#include "Distance.h"
#include "LineSensor.h"

#ifdef DEBUGGING
#warning Debugging uses alot of memory
#include <stdio.h>      // used for making debug strings
#include "freeMemory.h" // used for checking total free memory

// debug bot
void Bot::debug() {
    char buffer[MAX_BUFFER] = {0};
    snprintf(buffer, MAX_BUFFER, "<< Debugging Bot at %p >>", this);
    Serial.println(buffer);
    // motors
    Serial.println("(Left motor)");
    leftMotor.debug();
    Serial.println("(Right motor)");
    rightMotor.debug();
    #if CONTROL_TYPE == 0
    // joystick
    joystick.debug();
    #endif
    // distance
    distanceSensor.debug();
    // line
    lineSensor.debug();
}

// debug joystick
void JoystickController::debug() {
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
void MotorController::debug() {
    char buffer[MAX_BUFFER] = {0};
    snprintf(buffer, MAX_BUFFER, "<MotorController at %p>\n", this);
    Serial.print(buffer);
    snprintf(buffer, MAX_BUFFER, "powerPin:%d forwardPin:%d reversePin:%d\n", powerPin, forwardPin, reversePin);
    Serial.print(buffer);
    snprintf(buffer, MAX_BUFFER, "powerVal:%d forwardVal:%d reverseVal:%d\n", powerValue, forwardValue, reverseValue);
    Serial.print(buffer);
}

// debug distance sensor
void DistanceSensor::debug() {
    char buffer[MAX_BUFFER] = {0};
    snprintf(buffer, MAX_BUFFER, "<DistanceSensor at %p>\n", this);
    Serial.print(buffer);
    snprintf(buffer, MAX_BUFFER, "echoPin:%d triggerPin:%d distance:%dcm\n", echoPin, triggerPin, (int)read());
    Serial.print(buffer);
}

// debug line sensor
void LineSensor::debug() {
    char buffer[MAX_BUFFER] = {0};
    snprintf(buffer, MAX_BUFFER, "<LineSensor at %p>\n", this);
    Serial.print(buffer);
    snprintf(buffer, MAX_BUFFER, "Status: %d\n", read());
    Serial.print(buffer);
}
#else
#warning Debugging disabled
void Bot::debug() {}
void JoystickController::debug() {}
void MotorController::debug() {}
void DistanceSensor::debug() {}
void LineSensor::debug() {}
#endif