#include "Arduino.h"
#include "Constants.h"
#include "Bot.h"

void Bot::setDistancePins(int echo, int trigger) {
    distanceSensor.setPins(echo, trigger);
}

void Bot::setLinePin(int linePin) {
    lineSensor.setPin(linePin);
}
 