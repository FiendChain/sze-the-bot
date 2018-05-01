#define _USE_MATH_DEFINES
#include "AI_Types.h"
#include "BotSensors.h"
#include "Text.h"
#include <SFML/Window.hpp>
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
    // line sensor
    firstBot.addLineSensor(20, 0, 5);
    // add bot to arena
    sim.addBot(firstBot);
}

Movement AI_TypeA(AI &ai) {
    // internal variables
    static int foundBarrier = 0;
    // debug
    static sf::RenderWindow window(sf::VideoMode(800,600), "Bot Info");
    // get bot info
    float leftDistance = ai.distances.at(0);
    float rightDistance = ai.distances.at(1);
    int check = ai.lineChecks.at(0);
    // show bot info
    window.clear(sf::Color::Black);
    sf::Vector2f textPosition(0, 0);
    text.setPosition(textPosition);
    text.setCharacterSize(15);
    // distance data
    text.format("Left distance: %.0f", leftDistance);
    window.draw(text);
    text.format("Right distance: %.0f", rightDistance);
    textPosition.y += text.getCharacterSize();
    text.setPosition(textPosition);
    window.draw(text);
    window.display();
    // execute
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