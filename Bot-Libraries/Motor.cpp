#include "Arduino.h"
#include "Motor.h"
#include "Constants.h"
//#include <stdio.h>

MotorController::MotorController()
{
    setPins(UNKNOWN_PIN, UNKNOWN_PIN, UNKNOWN_PIN);
}

MotorController::MotorController(int power, int forward, int reverse)
{
    setPins(power, forward, reverse);
}

void MotorController::write(int power)
{
    if(powerPin == UNKNOWN_PIN || forwardPin == UNKNOWN_PIN || reversePin == UNKNOWN_PIN)
        return;
    // write to pins
    power = constrain(power, -MAX_PWM, MAX_PWM);
    analogWrite(powerPin, abs(power));
    // stop
    if(power == 0) {
        digitalWrite(forwardPin, LOW);
        digitalWrite(reversePin, LOW);
    // forward
    } else if(power > 0) {
        digitalWrite(forwardPin, HIGH);
        digitalWrite(reversePin, LOW);
    // reverse
    } else {
        digitalWrite(forwardPin, LOW);
        digitalWrite(reversePin, HIGH);
    }
}

void MotorController::setPins(int power, int forward, int reverse)
{
    pinMode(power, OUTPUT);
    pinMode(forward, OUTPUT);
    pinMode(reverse, OUTPUT);
    powerPin = power;
    forwardPin = forward;
    reversePin = reverse;
}