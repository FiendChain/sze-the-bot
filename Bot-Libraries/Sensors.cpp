#include "Arduino.h"
#include "Constants.h"
#include "Sensors.h"

Sensors::Sensors() {
    setLinePin(UNKNOWN_PIN);
}

void Sensors::setDistancePins(int _echoPin, int _triggerPin) {
    distance.setPins(_echoPin, _triggerPin);
}

void Sensors::setLinePin(int _linePin) {
    line.setPin(_linePin);
}

// get distance from primary proximity sensor
float Sensors::getDistance() {
    return distance.read();
}

// check if line sensor is in
int Sensors::checkInside() {
    return line.read();
}
