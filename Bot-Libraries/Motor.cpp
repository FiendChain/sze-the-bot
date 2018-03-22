#include "Arduino.h"
#include "Motor.h"
#include "Constants.h"

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
    powerValue = abs(power);
    analogWrite(powerPin, powerValue);
    // stop
    if(power == 0) {
        forwardValue = LOW;
        reverseValue = LOW;
    // forward
    } else if(power > 0) {
        forwardValue = HIGH;
        reverseValue = LOW;
    // reverse
    } else {
        forwardValue = LOW;
        reverseValue = HIGH;
    }
    digitalWrite(forwardPin, forwardValue);
    digitalWrite(reversePin, reverseValue);
}

void MotorController::setPins(int power, int forward, int reverse)
{
    pinMode(power, OUTPUT);
    pinMode(forward, OUTPUT);
    pinMode(reverse, OUTPUT);
    powerPin = power;
    forwardPin = forward;
    reversePin = reverse;
    powerValue = forwardValue = reverseValue = 0;
}