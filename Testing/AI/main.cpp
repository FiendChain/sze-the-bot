#include "Simulation.h"
#include "AI.h"
#include "Bot.h"
#include "Movement.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

void addRing(Simulation &sim, int total, float size, float distance, float x, float y);
Movement AI_TypeA(AI &ai);
Movement AI_TypeB(AI &ai);

int main(int argc, char *argv[]) {
    const int WIDTH = 1000;
    const int HEIGHT = 1000;
    const int FPS = 60;
    Simulation sim(WIDTH, HEIGHT, FPS, "Simulation");
    // creating circular barrier
    addRing(sim, 50, 20, HEIGHT/2.0f - 20, WIDTH/2.0f, HEIGHT/2.0f);
    // create smaller ring 
    // addRing(sim, 8, 20, 250, WIDTH/2.0f - 100, HEIGHT/2.0f - 100);
    
    // add bots
    Bot firstBot(20, WIDTH/2.0f, HEIGHT/2.0f);
    firstBot.addDistanceSensor(0, 0, 150, M_PI/2.0f, 101);
    firstBot.setAngle(M_PI);
    firstBot.setSpeed(50);
    firstBot.setAI(&AI_TypeA);
    sim.addBot(firstBot);
    // custom bot
    Bot secondBot(30, WIDTH/2.0f, HEIGHT/3.0f);
    secondBot.addDistanceSensor(0, 0, 200, M_PI/1.5f, 101);
    secondBot.addDistanceSensor(0, M_PI, 200, M_PI/1.5f, 101);
    secondBot.setAI(&AI_TypeB);
    sim.addBot(secondBot);
    // run program
    while(sim.run());

    return EXIT_SUCCESS;
}

Movement AI_TypeA(AI &ai) {
    float distance = ai.distances.at(0);
    if(distance < 100) {
        return LEFT;
    } else {
        return FORWARD;
    }
}

Movement AI_TypeB(AI &ai) {
    float distanceA = ai.distances.at(0);
    float distanceB = ai.distances.at(1);
    if(distanceA < 100) {
        return RIGHT;
    }
    if(distanceB < 50) {
        return LEFT;
    }
    return FORWARD;
}

void addRing(Simulation &sim, int total, float size, float distance, float x, float y) {
    float angle = 0;
    float angleIncrement = 2*M_PI/(float)total; 
    for(int i = 0; i < total; i++) {
        float objectX = distance * sin(angle) + x;
        float objectY = distance * cos(angle) + y;
        sim.addObstacle(size, objectX, objectY);
        angle += angleIncrement;
    }
}