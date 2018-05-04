#include "AI.h"
#include <stdio.h>

// default initialisation
AI::AI() {
    currentTime = 0;
    funcPtr = NULL;
};

// update the bot parameters
void AI::update(float dt, std::vector<float> _distances, std::vector<int> _lineChecks) {
    distances = _distances;
    lineChecks = _lineChecks;
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