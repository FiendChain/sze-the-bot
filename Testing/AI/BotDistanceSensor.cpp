#include "Bot.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Angles.h"

BotDistanceSensor::BotDistanceSensor(float _offsetDistance, float _angle, float maxRange, float fovAngle, float precision) 
:   distanceSensor(fovAngle, maxRange, precision),
    offsetDistance(_offsetDistance),
    angle(_angle),
    lastDistance(maxRange)
{
    
}

void BotDistanceSensor::update(sf::Vector2f position, float botAngle, std::vector<Entity> &objects) {
    float netAngle = angle+botAngle;
    netAngle = constrainAngle(netAngle);
    float actualAngle = M_PI/2.0f + netAngle;
    sf::Vector2f offsetPosition(-offsetDistance*sin(actualAngle), offsetDistance*cos(actualAngle));
    sf::Vector2f sensorPosition = position+offsetPosition;
    distanceSensor.setPosition(sensorPosition);
    lastDistance = distanceSensor.getDistance(netAngle, objects);
}

float BotDistanceSensor::getLastDistance() {
    return lastDistance;
}

void BotDistanceSensor::render(sf::RenderWindow &window) {
    distanceSensor.render(window);
}