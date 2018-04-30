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
    // add arena
    sim.addFloor(HEIGHT/2.0f, WIDTH/2.0f, HEIGHT/2.0f);
    // creating circular barrier
    // addRing(sim, 50, 20, HEIGHT/2.0f - 20, WIDTH/2.0f, HEIGHT/2.0f);
    // create smaller ring 
    // addRing(sim, 8, 20, 250, WIDTH/2.0f - 100, HEIGHT/2.0f - 100);
    
    // add bots
    Bot firstBot(20, WIDTH/2.0f, HEIGHT/2.0f);
    firstBot.addDistanceSensor(0, 0, 500, M_PI/2.0f, 101);
    firstBot.addLineSensor(20, 0, 5);
    firstBot.setAngle(M_PI);
    firstBot.setSpeed(50);
    firstBot.setAI(&AI_TypeA);
    sim.addBot(firstBot);
    // custom bot
    Bot secondBot(30, WIDTH/2.0f, HEIGHT/3.0f);
    secondBot.addDistanceSensor(0, 0, 500, M_PI/1.5f, 101);
    secondBot.addLineSensor(30, 0, 5);
    secondBot.setAI(&AI_TypeB);
    sim.addBot(secondBot);
    // run program
    while(sim.run());

    return EXIT_SUCCESS;
}

Movement AI_TypeA(AI &ai) {
    float distance = ai.distances.at(0);
    int check = ai.lineChecks.at(0);
    if(!check) {
        return RIGHT;
    }
    return FORWARD;
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