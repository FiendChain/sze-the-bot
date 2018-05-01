#define _USE_MATH_DEFINES
#include "Simulation.h"
#include "Text.h"
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
Text text;

Simulation::Simulation(int width, int height, int fps, const char *name)
:   window(sf::VideoMode(width, height), name)
{
    // physics
    this->fps = fps;
    timescale = 1.0f;
    currentTime = 0;
    dt = 1/(float)fps;
    // rendering
    window.setFramerateLimit(fps);
}

// main exec command
int Simulation::run() {
    pollEvents();
    int status = window.isOpen();
    if(status) {
        render();
        update();
    }
    return status;
}

// update simulation
void Simulation::update() {
    currentTime += dt;
    std::vector<Entity> obstacles;
    for(auto &e: objects) {
        e.update(dt);
        obstacles.push_back(e);
    }
    for(auto &b: bots) {
        obstacles.push_back(b);
    }
    for(auto &b: bots) {
        b.updateFOV(obstacles);
        b.updateLineSensor(floors);
        b.update(dt);
    }
}


// render all items
void Simulation::render() {
    window.clear(sf::Color::Black);
    for(auto &e: floors) {
        e.render(window);
    }
    for(auto &e: objects) {
        e.render(window);
    }
    for(auto &b: bots) {
        b.render(window);
    }
    showTelemetry();
    window.display();
}

// read events
void Simulation::pollEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
            return;
        } else if(event.type == sf::Event::KeyPressed) {
            const float timescaleIter = 0.1;
            switch(event.key.code) {
            case sf::Keyboard::Left:
                if(timescale > 0) timescale -= timescaleIter;
                if(timescale < 0) timescale = 0;
                dt = timescale/(float)fps;
                break;
            case sf::Keyboard::Right:
                timescale += timescaleIter;
                dt = timescale/(float)fps;
                break;
            }
        }
    }
}

// get window params
sf::Vector2u Simulation::getWindowSize() {
    return window.getSize();
}

// add an obstacle for distance sensor
void Simulation::addObstacle(float size, float x, float y) {
    Entity e(size, x, y);
    e.setFillColor(sf::Color::Red);
    objects.push_back(e);
}

// add a bot
void Simulation::addBot(Bot bot) {
    bots.push_back(bot);
}

// add a floor for line sensor
void Simulation::addFloor(float size, float x, float y) {
    Entity e(size, x, y);
    e.setFillColor(sf::Color::Blue);
    floors.push_back(e);
}

// show telemetry
void Simulation::showTelemetry() {
    int x = 15, y = 15;
    // time
    showText(x, y, 20, "Current time: %.3fs", currentTime);
    showText(x, y+20, 20, "Timescale: %.2f%%", timescale*100);
}

void Simulation::showText(int x, int y, int size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    text.vformat(format, args);
    va_end(args); 
    text.setPosition(x, y);
    text.setCharacterSize(size);
    window.draw(text);
}
