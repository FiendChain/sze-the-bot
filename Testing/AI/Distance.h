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
        const float fovAngle;   // distance sensor params
        const float fovPoints;
        const float maxRange;
        sf::Vector2f position;
        std::vector<sf::Vertex> fov;
        int checkAngle(float angle, Entity &object);
        float readAngle(float angle, std::vector<Entity> &objects);
};

#endif