#include "AI.h"
#include <stdio.h>

// default initialisation
AI::AI() {
    isInside = 0;
    currentTime = 0;
    funcPtr = NULL;
};

// update the bot parameters
void AI::update(float dt, std::vector<float> _distances, int _isInside) {
    distances = _distances;
    isInside = _isInside;
    currentTime += dt*1000;
}

// get the move from the bot
Movement AI::getMove() {
    if(funcPtr == NULL) {   // run basic ai
        return STOP;
    } else {
        return funcPtr(*this);
    }
    
}

// set AI function
void AI::setFunctionPointer(Movement (*_funcPtr)(AI &)) {
    funcPtr = _funcPtr;
}