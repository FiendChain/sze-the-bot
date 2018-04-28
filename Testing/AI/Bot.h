#ifndef _BOT_H_
#define _BOT_H_
#define FOV_POINTS 31 // make it off to have a centre fov line
#define MAX_RANGE 500

#include <SFML/Graphics.hpp>
#include "AI.h"
#include "Entity.h"
#include "Distance.h"
#include <vector>

class Bot: Entity {
    public:
        Bot();
        Bot(float size, float x, float y);
        // get reference to body for analysis
        Entity &getBody();
        // set bot specifications
        void setSpeed(float speed);
        void setAngle(float angle);
        // render and update methods
        void render(sf::RenderWindow &window);
        void update(float dt, std::vector<Entity> &objects);
    private:
        // bot parts
        AI ai;
        Entity body;
        DistanceSensor distanceSensor;
        // bot params
        float botSpeed;
        float turnRate;
        float botAngle;
        // bot actions
        void move(Movement move, float dt);
        // make sure angle stays between -PI and PI
        float constrainAngle(float _angle);
};

#endif