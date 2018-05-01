#include "Angles.h"
#include "LineSensor.h"
#include <stdio.h>

LineSensor::LineSensor(float range) {
    setRadius(range);
    setOrigin(range, range);
    setFillColor(sf::Color::Yellow);
    setOutlineColor(sf::Color::White);
}

int LineSensor::check(std::vector<Entity> &floors) {
    for(auto &e: floors) {
        float R = e.getSize();
        float maxDistance = R-getRadius();
        sf::Vector2f posDiff = getPosition()-e.getPosition();
        float distance = absFloat(posDiff);
        if(distance > maxDistance) {
            setFillColor(sf::Color::Red);
            return 0;
        }
    }
    setFillColor(sf::Color::Yellow);
    return 1;
}

void LineSensor::render(sf::RenderWindow &window) {
    window.draw(*this);
}