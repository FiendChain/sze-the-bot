#include "Simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define _USE_MATH_DEFINES
#include <math.h>

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
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
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
        b.update(dt);
        b.updateFOV(obstacles);
    }
}


// render all items
void Simulation::render() {
    window.clear(sf::Color::Black);
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

// add an obstacle
void Simulation::addObstacle(float size, float x, float y) {
    Entity e(size, x, y);
    e.setFillColor(sf::Color::Red);
    objects.push_back(e);
}

void Simulation::addBot(Bot &bot) {
    bots.push_back(bot);
}

// show telemetry
void Simulation::showTelemetry() {
    int x = 15, y = 15;
    // time
    showText(x, y, 15, "Current time: %.3fs", currentTime);
    showText(x, y+20, 15, "Timescale: %.2f%%", timescale*100);
}

void Simulation::showText(int x, int y, int size, const char *format, ...) {
    char buffer[256] = {0};
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    text.setString(buffer);
    text.setPosition(x, y);
    text.setCharacterSize(size);
    window.draw(text);
}