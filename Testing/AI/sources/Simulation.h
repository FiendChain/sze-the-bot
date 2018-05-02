#ifndef _RENDER_H_
#define _RENDER_H_

#include "Bot.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Simulation {
    public:
        Simulation(int width, int height, int fps, const char *name);
        int run();
        void addObstacle(float size, float x, float y);
        void addFloor(float size, float x, float y);
        void addBot(Bot bot);
        sf::Vector2u getWindowSize();
    private:
        // simulation entities
        std::vector<Entity> objects;
        std::vector<Bot> bots;
        std::vector<Entity> floors;
        // rendering
        sf::RenderWindow window;
        // simulation parameters
        int fps;
        float dt;   // timescale
        float currentTime;
        float timescale;
        // methods
        void update();
        void render();
        void pollEvents();
        void showTelemetry();
        void showText(int x, int y, int size, const char *format, ...);
};

#endif