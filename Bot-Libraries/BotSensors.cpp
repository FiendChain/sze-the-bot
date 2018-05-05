#include "Arduino.h"
#include "Constants.h"
#include "Bot.h"

void Bot::setLeftDistancePins(int echo, int trigger) {
    leftDistanceSensor.setPins(echo, trigger);
}

void Bot::setRightDistancePins(int echo, int trigger) {
    rightDistanceSensor.setPins(echo, trigger);
}

void Bot::setLinePin(int linePin) {
    lineSensor.setPin(linePin);
}

void Bot::getSensorData(float &leftDistance, float &rightDistance, int &isOutside) {
    leftDistance = leftDistanceSensor.read();
    rightDistance = rightDistanceSensor.read();
    isOutside = lineSensor.read();
}
 