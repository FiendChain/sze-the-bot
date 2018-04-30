#include "Entity.h"

Entity::Entity() {
    setSize(0);
    setPosition(0, 0);
    setVelocity(0, 0);
    setFillColor(sf::Color::White);
}

Entity::Entity(float size, float x, float y) {
    setSize(size);
    setPosition(x, y);
    setVelocity(0, 0);
    setFillColor(sf::Color::White);
}

// update body
void Entity::update(float dt) {
    setPosition(getPosition() + velocity*dt);
}

void Entity::render(sf::RenderWindow &window) {
    window.draw(*this);
}

// add velocity attributes
sf::Vector2f Entity::getVelocity() {
    return velocity;
}

void Entity::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

// size attribute
float Entity::getSize() {
    return getRadius();
}

void Entity::setSize(float size) {
    setOrigin(size, size); //centre 
    setRadius(size);
}