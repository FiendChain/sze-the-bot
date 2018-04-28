#include "Simulation.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc, char *argv[]) {
    const int WIDTH = 1000;
    const int HEIGHT = 1000;
    const int FPS = 60;
    Simulation sim(WIDTH, HEIGHT, FPS, "Simulation");
    // creating circular barrier
    float angle = 0;
    int totalObjects = 50;
    float angleIncrement = 2*M_PI/(float)totalObjects; 
    float size = 20;
    float distance = HEIGHT/2.0f - size;
    float x = WIDTH/2.0f, y = HEIGHT/2.0f;
    for(int i = 0; i < totalObjects; i++) {
        float objectX = distance * sin(angle) + x;
        float objectY = distance * cos(angle) + y;
        sim.addObstacle(size, objectX, objectY);
        angle += angleIncrement;
    }
    // add bots
    sim.addBot(20, WIDTH/2.0f, HEIGHT/2.0f, 0);
    // run program
    while(sim.run());

    return EXIT_SUCCESS;
}