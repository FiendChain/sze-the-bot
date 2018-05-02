#include "Angles.h"
#include "Entity.h"

Entity::Entity() {
    setSize(0);
    setPosition(0, 0);
    setVelocity(0, 0);
    setAcceleration(0, 0);
    setFillColor(sf::Color::White);
}

Entity::Entity(float size, float x, float y) {
    setSize(size);
    setPosition(x, y);
    setVelocity(0, 0);
    setAcceleration(0, 0);
    setFillColor(sf::Color::White);
}

// update body
void Entity::update(float dt) {
    velocity += acceleration * dt;
    setPosition(getPosition() + velocity*dt);
    setAcceleration(0, 0);
}

void Entity::render(sf::RenderWindow &window) {
    window.draw(*this);
}


// WORK ON THIS
void Entity::collide(std::vector<Entity> &entities) {
    for(Entity &e: entities) {
        // check if possible collision
        sf::Vector2f posDiff = e.getPosition()-getPosition();
        float distance = absFloat(posDiff);
        float R_self = getSize();
        float R_other = e.getSize();
        float minDistance = absFloat(R_self-R_other);
        if(distance > minDistance) continue;
        if(distance <= R_self) continue;
        sf::Vector2f deltaAccSelf = e.getVelocity();
        sf::Vector2f deltaAccOther = getVelocity();
        applyForce(deltaAccSelf);
        e.applyForce(deltaAccOther);
        printf("Collision: %.0f > %.0f\n", distance, minDistance);
    }
}

// add velocity attributes
sf::Vector2f Entity::getVelocity() {
    return velocity;
}

void Entity::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

// acceleration
sf::Vector2f Entity::getAcceleration() {
    return acceleration;
}

void Entity::setAcceleration(float x, float y) {
    acceleration.x = x;
    acceleration.y = y;
}

void Entity::setAcceleration(sf::Vector2f _acceleration) {
    acceleration = _acceleration;
}

// apply forces
void Entity::applyForce(sf::Vector2f force) {
    acceleration += force;
}

// size attribute
float Entity::getSize() {
    return getRadius();
}

void Entity::setSize(float size) {
    setOrigin(size, size); //centre 
    setRadius(size);
}