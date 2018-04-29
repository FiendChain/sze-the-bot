#include "Bot.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Angles.h"

Bot::Bot(float size, float x, float y)
{
    // init bot param
    setSize(size);
    setPosition(x, y);
    setFillColor(sf::Color::Green);
    currentMove = STOP;
    botSpeed = 50;
    botAngle = 0;
    turnRate = M_PI/4.0f;
}

// bot setters
void Bot::setAngle(float angle) {
    botAngle = angle;
}

void Bot::setSpeed(float speed) {
    botSpeed = speed;
}

void Bot::setAI(Movement (*funcPtr)(AI &)) {
    ai.setFunctionPointer(funcPtr);
}

// render the bot
void Bot::renderFOV(sf::RenderWindow &window) {
    for(auto &sensor: distanceSensors) {
        sensor.render(window);
    }
}

// update the fov
void Bot::updateFOV(std::vector<Entity> &objects) {
    for(auto &sensor: distanceSensors) {
        sensor.update(getPosition(), botAngle, objects);
    }
}

// update the bot
void Bot::update(float dt) {
    std::vector<float> distances;
    for(auto &sensor: distanceSensors) {
        distances.push_back(sensor.getLastDistance());
    }
    ai.update(dt, distances, 1);
    currentMove = ai.getMove();
    move(dt);
    setPosition(getPosition() + getVelocity()*dt);
}

void Bot::render(sf::RenderWindow &window) {
    window.draw(*this);
    renderFOV(window);
}

// move the bot
void Bot::move(float dt) {
    switch(currentMove) {
    case FORWARD:
        setVelocity(-botSpeed*sin(botAngle), botSpeed*cos(botAngle));
        break;
    case BACKWARD:
        setVelocity(botSpeed*sin(botAngle), -botSpeed*cos(botAngle));
        break;
    case LEFT:
        setVelocity(0, 0);
        botAngle -= turnRate*dt;    // invert direction to turn, since y-axis is inverted on display
        botAngle = constrainAngle(botAngle);
        break;
    case RIGHT:
        setVelocity(0, 0);
        botAngle += turnRate*dt;
        botAngle = constrainAngle(botAngle);
        break;
    case STOP:
        setVelocity(0, 0);
        break;
    }
}

// add distance sensors to the bot
void Bot::addDistanceSensor(float offsetDistance, float angle, float maxRange, float fovRange, float precision) {
    BotDistanceSensor distanceSensor(offsetDistance, angle, maxRange, fovRange, precision);
    distanceSensors.push_back(distanceSensor);
}
