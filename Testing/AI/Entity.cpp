#include "Entity.h"

Entity::Entity() {
    setSize(0);
    setPosition(0, 0);
    setVelocity(0, 0);
    setColor(sf::Color::White);
}

Entity::Entity(float size, float x, float y) {
    setSize(size);
    setPosition(x, y);
    setVelocity(0, 0);
    setColor(sf::Color::White);
}

// update body
void Entity::update(float dt) {
    sf::Vector2f currPos = body.getPosition();
    sf::Vector2f newPos = currPos + velocity * dt;
    body.setPosition(newPos);
}

// render main body
void Entity::render(sf::RenderWindow &window) {
    window.draw(body);
}

// get params
sf::Vector2f Entity::getPosition() {
    return body.getPosition();
}

sf::Vector2f Entity::getVelocity() {
    return velocity;
}

// get radius of round entity
float Entity::getSize() {
    return body.getRadius();
}

// set params
void Entity::setColor(const sf::Color &color) {
    body.setFillColor(color);
}

void Entity::setPosition(float x, float y) {
    body.setPosition(x, y);
}

void Entity::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

void Entity::setSize(float size) {
    body.setOrigin(size, size); //centre 
    body.setRadius(size);
}