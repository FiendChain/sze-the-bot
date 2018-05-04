#include "AI.h"
#include "Arduino.h"
#include "Constants.h"

// default initialisation
AI::AI() {
    leftDistance = 0;
    rightDistance = 0;
    isInside = 0;
    currentTime = millis();
    func = NULL;
};

// update the bot parameters
void AI::update(float _leftDistance, float _rightDistance, int _isInside) {
    leftDistance = _leftDistance;
    rightDistance = _rightDistance;
    isInside = _isInside;
    currentTime = millis();
}

// get the move from the bot
Movement AI::getMove() {
    if(func == NULL) {
        return STOP;
    } else {
        return func(leftDistance, rightDistance, isInside);
    }
}

// ai function
void AI::setAI(Movement (*_func)(float, float, int)) {
    func = _func;
}