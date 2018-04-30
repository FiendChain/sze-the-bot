#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// similar to sf::CircleShape except it also have a velocity
class Entity: public sf::CircleShape {
    public:
        Entity();
        Entity(float size, float x, float y);
        // set params
        void setSize(float size);
        void setVelocity(float x, float y);
        // get params
        float getSize();
        sf::Vector2f getVelocity();
        // update and render
        void update(float dt);
        void render(sf::RenderWindow &window);
    private:
        sf::Vector2f velocity;
};

#endif