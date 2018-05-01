#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

// similar to sf::CircleShape except it also have a velocity
class Entity: public sf::CircleShape {
    public:
        Entity();
        Entity(float size, float x, float y);
        // set params
        void setSize(float size);
        void setVelocity(float x, float y);
        void setAcceleration(float x, float y);
        void setAcceleration(sf::Vector2f _acceleration);
        void applyForce(sf::Vector2f force);
        // get params
        float getSize();
        sf::Vector2f getVelocity();
        sf::Vector2f getAcceleration();
        // update and render
        void update(float dt);
        void render(sf::RenderWindow &window);
        void collide(std::vector<Entity> &entities);
    private:
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
};

#endif