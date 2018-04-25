#include "Arduino.h"  
#include "Motor.h"
#include "Constants.h"

MotorController::MotorController() {
    setPins(UNKNOWN_PIN, UNKNOWN_PIN, UNKNOWN_PIN);
}

MotorController::MotorController(int _powerPin, int _forwardPin, int _reversePin) {
    setPins(_powerPin, _forwardPin, _reversePin);
}

// given a value from -255 to 255(MAX_PWM) move the motor
// the motor is controller through 3 pins: forward, reverse, power
// forward: LOW, HIGH => If HIGH make motor go forward
// reverse: LOW, HIGH => If HIGH make motor go reverse
// power: 0..255 => Determines how fast the motor goes
// only forward or reverse can be on exclusively
void MotorController::write(int power) {
    if(powerPin == UNKNOWN_PIN || forwardPin == UNKNOWN_PIN || reversePin == UNKNOWN_PIN) {
        return;
    }
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

// set the pins and autoconfigure their pin mode
void MotorController::setPins(int _powerPin, int _forwardPin, int _reversePin) {
    powerPin = _powerPin;
    forwardPin = _forwardPin;
    reversePin = _reversePin;
    powerValue = forwardValue = reverseValue = 0;
    // only set pin mode if valid
    if(powerPin != UNKNOWN_PIN && forwardPin != UNKNOWN_PIN && reversePin != UNKNOWN_PIN) {
        pinMode(powerPin, OUTPUT);
        pinMode(forwardPin, OUTPUT);
        pinMode(reversePin, OUTPUT);
    }
}