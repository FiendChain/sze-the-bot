#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// similar to sf::CircleShape except it also have a velocity
class Entity {
    public:
        Entity();
        Entity(float size, float x, float y);
        // set params
        void setSize(float size);
        void setColor(const sf::Color &color);
        void setPosition(float x, float y);
        void setVelocity(float x, float y);
        // get params
        sf::Vector2f getPosition();
        sf::Vector2f getVelocity();
        float getSize();
        // update and render
        void update(float dt);
        void render(sf::RenderWindow &window);
    private:
        sf::CircleShape body;
        sf::Vector2f velocity;
};

#endif