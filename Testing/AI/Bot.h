#ifndef _BOT_H_
#define _BOT_H_
#define FOV_POINTS 31 // make it off to have a centre fov line
#define MAX_RANGE 500

#include <SFML/Graphics.hpp>
#include "AI.h"
#include "Entity.h"
#include "Distance.h"
#include "Movement.h"
#include <vector>

class BotDistanceSensor {
    public:
        BotDistanceSensor(float _offsetDistance, float _angle, float maxRange, float fovAngle, float precision);
        void update(sf::Vector2f position, float botAngle, std::vector<Entity> &objects);
        void render(sf::RenderWindow &window);
        float getLastDistance();
    private:
        DistanceSensor distanceSensor;
        float lastDistance;
        float offsetDistance;
        float angle;
};

class Bot: public Entity {
    public:
        Bot(float size, float x, float y);
        // set bot specifications
        void setSpeed(float speed);
        void setAngle(float angle);
        void setAI(Movement (*funcPtr)(AI &));
        // distance sensors
        void addDistanceSensor(float offsetDistance, float angle, float maxRange, float fovRange, float precision);
        void renderFOV(sf::RenderWindow &window);
        void updateFOV(std::vector<Entity> &objects);
        // update and render
        void update(float dt);
        void render(sf::RenderWindow &window); // override default render
    private:
        // bot parts
        AI ai;
        std::vector<BotDistanceSensor> distanceSensors;
        // bot params
        float botSpeed;
        float turnRate;
        float botAngle;
        Movement currentMove;
        // bot actions
        void move(float dt);
};

#endif