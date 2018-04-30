#ifndef _BOT_H_
#define _BOT_H_
#define FOV_POINTS 31 // make it off to have a centre fov line
#define MAX_RANGE 500

#include <SFML/Graphics.hpp>
#include "AI.h"
#include "Entity.h"
#include "BotSensors.h"
#include "Movement.h"
#include <vector>

class Bot: public Entity {
    public:
        Bot(float size, float x, float y);
        // set bot specifications
        void setSpeed(float speed);
        void setAngle(float angle);
        void setAI(Movement (*funcPtr)(AI &));
        // distance sensors
        void addDistanceSensor(float offsetDistance, float angle, float maxRange, float fovRange, float precision);
        void addLineSensor(float offsetDistance, float angle, float range);
        // update and render
        void update(float dt);
        void updateFOV(std::vector<Entity> &objects);
        void updateLineSensor(std::vector<Entity> &floors);
        void render(sf::RenderWindow &window); // override default render
    private:
        // bot parts
        AI ai;
        std::vector<BotDistanceSensor> distanceSensors;
        std::vector<BotLineSensor> lineSensors;
        // bot params
        float botSpeed;
        float turnRate;
        float botAngle;
        Movement currentMove;
        // bot actions
        void move(float dt);
        // render parts
        void renderFOV(sf::RenderWindow &window);
        void renderLineSensor(sf::RenderWindow &window);
};

#endif