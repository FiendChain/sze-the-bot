#include "AI.h"
// default initialisation
AI::AI() {
    distance = 0;
    isInside = 0;
    currentTime = 0;
};

// update the bot parameters
void AI::update(float _distance, int _isInside) {
    distance = _distance;
    isInside = _isInside;
    currentTime++;
}

// get the move from the bot
Movement AI::getMove() {
    if(distance < 5) {
        return LEFT;
    } else {
        return FORWARD;
    }
}