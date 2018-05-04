#define _USE_MATH_DEFINES
#include "AI_Types.h"
#include "Angles.h"
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
    float range = 600;
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
    Movement move = STOP;
    // show bot info
    console.clear();
    // distance data
    console.print("Left distance: %.0f", leftDistance);
    console.print("Right distance: %.0f", rightDistance);
    console.print("Current time: %.0f", currentTime);
    
    // rotate to avoid edge
    if(reachedEdge) {
        if(currentTime-turnTime < 1000) {
            move = RIGHT;
        } else {
            reachedEdge = 0;
            move = FORWARD;
        }
    } else {
        // move forward into edge
        if(!checkFront) {
            reachedEdge = 1;
            turnTime = currentTime;
            move = BACKWARD;
        // reverse into edge
        } else if(!checkBack) {
            reachedEdge = 1;
            turnTime = currentTime;
            move = FORWARD;
        }
    }
    //if not avoiding being knocked out of arena
    if(!reachedEdge) {
        //if object found, try to centre
        if(leftDistance < 600 && rightDistance < 600) {
            if(absFloat(leftDistance-rightDistance) < 60) {
                move = FORWARD;
            }
            if(absFloat(leftDistance-rightDistance) > 60) {
                if(leftDistance < rightDistance) {
                    move = LEFT;
                } else if(rightDistance > leftDistance) {
                    move = RIGHT;
                } else {
                    move = FORWARD;
                }
            }
        // if nothing found and not on edge, rotate until find somethinf
        } else {
            move = RIGHT;
        }
    }
    // print current move
    const char *moveText = "Current move: %s";
    switch(move) {
    case FORWARD:
        console.print(moveText, "forward");
        break;
    case BACKWARD:
        console.print(moveText, "backward");
        break;
    case LEFT:
        console.print(moveText, "left");
        break;
    case RIGHT:
        console.print(moveText, "right");
        break;
    case STOP:
        console.print(moveText, "stop");
        break;
    }
    // display debug
    console.display();
    return move;
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