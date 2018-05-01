#define _USE_MATH_DEFINES
#include "AI_Types.h"
#include <math.h>

// BOT A
void addBotA(Simulation &sim) {
    sf::Vector2u size = sim.getWindowSize();
    Bot firstBot(20, size.x/2.0f, size.y/2.0f);
    firstBot.addDistanceSensor(0, 0, 200, M_PI/5.0f, 31);
    firstBot.addLineSensor(20, 0, 5);
    firstBot.setAngle(M_PI);
    firstBot.setSpeed(50);
    firstBot.setAI(&AI_TypeA);
    sim.addBot(firstBot);
}

Movement AI_TypeA(AI &ai) {
    static int foundBarrier = 0;
    float distance = ai.distances.at(0);
    int check = ai.lineChecks.at(0);
    if(foundBarrier) {
        return BACKWARD;
    }
    if(!check) {
        foundBarrier = 1;
        return STOP;
    }
    return FORWARD;
} 

// BOT B
void addBotB(Simulation &sim) {
    sf::Vector2u size = sim.getWindowSize();
    Bot secondBot(30, size.x/2.0f, size.y/3.0f);
    secondBot.addDistanceSensor(0, 0, 500, M_PI/1.5f, 101);
    secondBot.addLineSensor(30, 0, 5);
    secondBot.setAI(&AI_TypeB);
    sim.addBot(secondBot);
}

Movement AI_TypeB(AI &ai) {
    float distance = ai.distances.at(0);
    int check = ai.lineChecks.at(0);
    if(!check) {
        return RIGHT;
    }
    if(distance < 500) {
        return FORWARD;
    } else {
        return LEFT;
    }
}