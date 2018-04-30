#ifndef _LINE_SENSOR_H_
#define _LINE_SENSOR_H_
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>

class LineSensor: public sf::CircleShape {
    public:
        LineSensor(float range);
        int check(std::vector<Entity> &floors);
        void render(sf::RenderWindow &window);
};

#endif