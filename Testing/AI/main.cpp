#define _USE_MATH_DEFINES
#include "sources/AI_Types.h"
#include "sources/Simulation.h"
#include <math.h>
#include <stdio.h>

void addRing(Simulation &sim, int total, float size, float distance, float x, float y);

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
    // add one object for targetting
    sim.addObstacle(20, WIDTH/2.0f + 100, HEIGHT/2.0f - 300);

    // add bots
    addBotA(sim);
    // addBotB(sim);

    // run program
    while(sim.run());

    return EXIT_SUCCESS;
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