#include "Bot.h"
#define _USE_MATH_DEFINES
#include <math.h>

Bot::Bot()
:   body(0, 0, 0),
    distanceSensor(0, 0, 0)
{
    botSpeed = 0;
    botAngle = 0;
    turnRate = 0;
}

Bot::Bot(float size, float x, float y)
:   body(size, x, y),
    distanceSensor(M_PI/3.0f, 300, 201)
{
    // init bot param
    body.setColor(sf::Color::Green);
    botSpeed = 50;
    botAngle = 0;
    turnRate = M_PI/4.0f;
}

// get body for collision checking
Entity &Bot::getBody() {
    return body;
}

// bot setters
void Bot::setAngle(float angle) {
    botAngle = angle;
}

void Bot::setSpeed(float speed) {
    botSpeed = speed;
}

// render the bot
void Bot::render(sf::RenderWindow &window) {
    body.render(window);
    distanceSensor.render(window);
}

// update the bot
void Bot::update(float dt, std::vector<Entity> &objects) {
    distanceSensor.setPosition(body.getPosition());
    float distance = distanceSensor.getDistance(botAngle, objects);
    ai.update(dt, distance, 1);
    Movement moveType = ai.getMove();
    move(moveType, dt);
    body.update(dt);
}

// move the bot
void Bot::move(Movement move, float dt) {
    switch(move) {
    case FORWARD:
        body.setVelocity(-botSpeed*sin(botAngle), botSpeed*cos(botAngle));
        break;
    case BACKWARD:
        body.setVelocity(botSpeed*sin(botAngle), -botSpeed*cos(botAngle));
        break;
    case LEFT:
        body.setVelocity(0, 0);
        botAngle -= turnRate*dt;    // invert direction to turn, since y-axis is inverted on display
        botAngle = constrainAngle(botAngle);
        break;
    case RIGHT:
        body.setVelocity(0, 0);
        botAngle += turnRate*dt;
        botAngle = constrainAngle(botAngle);
        break;
    case STOP:
        body.setVelocity(0, 0);
        break;
    }
}

// constrain angle between -Pi(right) and PI(left)
float Bot::constrainAngle(float angle) {
    while(angle > M_PI) {
        angle -= 2*M_PI;
    }
    while(angle < -M_PI) {
        angle += 2*M_PI;
    }
    return angle;
}
