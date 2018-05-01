#define _USE_MATH_DEFINES
#include "AI_Types.h"
#include "BotSensors.h"
#include "Text.h"
#include "DebugConsole.h"
#include <math.h>

// BOT A
void addBotA(Simulation &sim) {
    sf::Vector2u size = sim.getWindowSize();
    // configure bot
    float botSize = 20;
    Bot firstBot(botSize, size.x/2.0f, size.y/2.0f);
    firstBot.setAngle(M_PI);
    firstBot.setSpeed(50);
    firstBot.setAI(&AI_TypeA);
    // distance sensor specs
    float fov = M_PI/5.0f;
    float range = 200;
    float precision = 31;
    float rotateAngle = M_PI/4.0f;
    // left sensor
    BotDistanceSensor leftDistanceSensor(range, fov, precision);
    leftDistanceSensor.setOffset(botSize, rotateAngle);
    leftDistanceSensor.setRotate(0, true);
    firstBot.addDistanceSensor(leftDistanceSensor);
    // right sensor
    BotDistanceSensor rightDistanceSensor(range, fov, precision);
    rightDistanceSensor.setOffset(botSize, -rotateAngle);
    rightDistanceSensor.setRotate(0, true);
    firstBot.addDistanceSensor(rightDistanceSensor);
    // front line sensor
    firstBot.addLineSensor(botSize, 0, 5);
    firstBot.addLineSensor(botSize, M_PI, 5);
    // add bot to arena
    sim.addBot(firstBot);
}

Movement AI_TypeA(AI &ai) {
    // internal variables
    static int foundBarrier = 0;
    static Movement currentMove = FORWARD;
    static int reachedEdge = 0;
    static float turnTime = 0;
    // debug
    static DebugConsole console(sf::VideoMode(800,600), "Bot Info");
    console.setCharacterSize(15);
    // get bot info
    float leftDistance = ai.distances.at(0);
    float rightDistance = ai.distances.at(1);
    int checkFront = ai.lineChecks.at(0);
    int checkBack = ai.lineChecks.at(1);
    float currentTime = ai.currentTime;
    // show bot info
    console.clear();
    // distance data
    console.print("Left distance: %.0f", leftDistance);
    console.print("Right distance: %.0f", rightDistance);
    console.print("Current time: %.0f", currentTime);
    console.display();
    // execute
    if(reachedEdge) {
        if(currentTime-turnTime < 1000) {
            return RIGHT;
        } else {
            reachedEdge = 0;
            return FORWARD;
        }
    }
    if(!checkFront) {
        reachedEdge = 1;
        turnTime = currentTime;
        return BACKWARD;
    }
    if(!checkBack) {
        reachedEdge = 1;
        turnTime = currentTime;
        return FORWARD;
    }
    if(leftDistance < 150 || rightDistance < 150) {
        return FORWARD;
    }
    if(leftDistance < 100 && rightDistance < 100) {
        if(leftDistance < rightDistance) {
            return LEFT;
        } else if(rightDistance > leftDistance) {
            return RIGHT;
        } else {
            return FORWARD;
        }
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