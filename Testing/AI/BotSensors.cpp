#include "Bot.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Angles.h"
#include <stdio.h>
#include "Text.h"

// base bot sensor class
BotSensor::BotSensor() {
    setOffset(0, 0);
}

void BotSensor::setOffset(float _offsetDistance, float _angle) {
    angle = _angle;
    offsetDistance = _offsetDistance;
}

void BotSensor::render(sf::RenderWindow &window) {
    // override this
}

// distance sensor
BotDistanceSensor::BotDistanceSensor(float maxRange, float fovAngle, float precision) 
:   distanceSensor(fovAngle, maxRange, precision),
    lastDistance(maxRange)
{
    setOffset(0, 0);
}

void BotDistanceSensor::update(sf::Vector2f position, float botAngle, std::vector<Entity> &objects) {
    float netAngle = constrainAngle(angle+botAngle);
    sf::Vector2f offsetPosition = getRectFromPolar(offsetDistance, netAngle);
    sf::Vector2f sensorPosition = position+offsetPosition;
    distanceSensor.setPosition(sensorPosition);
    lastDistance = distanceSensor.getDistance(netAngle, objects);
}

float BotDistanceSensor::getLastDistance() {
    return lastDistance;
}

void BotDistanceSensor::render(sf::RenderWindow &window) {
    text.format("distance: %.0f", lastDistance);
    sf::Vector2f offset(20, 10);
    text.setPosition(offset+distanceSensor.getPosition());
    window.draw(text);
    distanceSensor.render(window);
}

// line sensor
BotLineSensor::BotLineSensor(float range) 
:   lineSensor(range),
    lastCheck(0)
{
    
}

void BotLineSensor::update(sf::Vector2f position, float botAngle, std::vector<Entity> &floors) {
    float netAngle = constrainAngle(angle+botAngle);
    sf::Vector2f offsetPosition = getRectFromPolar(offsetDistance, netAngle);
    sf::Vector2f sensorPosition = position+offsetPosition;
    lineSensor.setPosition(sensorPosition);
    lastCheck = lineSensor.check(floors);
}

void BotLineSensor::render(sf::RenderWindow &window) {
    lineSensor.render(window);
}

int BotLineSensor::getLastCheck() {
    return lastCheck;
}