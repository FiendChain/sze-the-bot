#include "AI.h"

// default initialisation
AI::AI() {
    distance = 0;
    isInside = 0;
    currentTime = 0;
};

// update the bot parameters
void AI::update(float dt, float _distance, int _isInside) {
    distance = _distance;
    isInside = _isInside;
    currentTime += dt*1000;
}

// get the move from the bot
Movement AI::getMove() {
    if(distance < 100) {
        return LEFT;
    } else {
        return FORWARD;
    }
}