#ifndef _DISTANCE_H_
#define _DISTANCE_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

// distance sensor
class DistanceSensor {
    public:
        DistanceSensor(float _fovAngle, float _maxRange, float _fovPoints);
        void setPosition(sf::Vector2f _position);
        void setPosition(float x, float y);
        sf::Vector2f getPosition();
        float getDistance(float angle, std::vector<Entity> &objects);
        void render(sf::RenderWindow &window);
    private:
        // distance sensor params
        const float fovAngle;   
        const float fovPoints;
        const float maxRange;
        sf::Vector2f position;
        std::vector<sf::Vertex> fov;
        // get distance methods
        int checkAngle(float angle, Entity &object);
        float readAngle(float angle, std::vector<Entity> &objects);
        float getDistanceEntity(float angle, Entity &e);
        float getVerticalDistance(Entity &e);
        float getNonVerticalDistance(float m, float b, Entity &e);
};

#endif