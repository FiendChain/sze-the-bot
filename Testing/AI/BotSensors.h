#ifndef _BOT_SENSORS_H_
#define _BOT_SENSORS_H_

#include "Distance.h"
#include "LineSensor.h"
#include <SFML/Graphics.hpp>
#include <vector>

class BotSensor {
    public:
        BotSensor();
        void setOffset(float _offsetDistance, float _offsetAngle);
        void render(sf::RenderWindow &window);
        float offsetAngle;
        float offsetDistance;
};

class BotDistanceSensor: public BotSensor {
    public:
        BotDistanceSensor(float maxRange, float fovAngle, float precision);
        void setRotate(float _rotateAngle, int _rotateLock);
        void update(sf::Vector2f position, float botAngle, std::vector<Entity> &objects);
        void render(sf::RenderWindow &window);
        float getLastDistance();
    private:
        // parameters for angle lock
        float rotateAngle;
        int rotateLock;   // 0 = relative to overall angle, 1 = relative to botAngle 
        DistanceSensor distanceSensor;
        float lastDistance;
};

class BotLineSensor: public BotSensor {
    public:
        BotLineSensor(float range);
        void update(sf::Vector2f position, float botAngle, std::vector<Entity> &floors);
        void render(sf::RenderWindow &window);
        int getLastCheck();
    private:
        LineSensor lineSensor;
        int lastCheck;
};

#endif