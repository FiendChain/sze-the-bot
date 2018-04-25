#include "Arduino.h"
#include "Constants.h"
#include "LineSensor.h"

LineSensor::LineSensor() {
    setPin(UNKNOWN_PIN);
}

LineSensor::LineSensor(int _readPin) {
    setPin(_readPin);
}

// set pin
void LineSensor::setPin(int _readPin) {
    readPin = _readPin;
    if(readPin != UNKNOWN_PIN) {
        pinMode(readPin, INPUT);
    }
}

// read a low or high value
int LineSensor::read() {
    if(readPin == UNKNOWN_PIN) {
        return 0;
    }
    int status = digitalRead(readPin);
    return status;
}