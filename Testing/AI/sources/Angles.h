#ifndef _ANGLES_H_
#define _ANGLES_H_
#include <SFML/Graphics.hpp>

float absFloat(float value);
float absFloat(sf::Vector2f &v);
float constrainAngle(float angle);
float getAngle(float x, float y);
sf::Vector2f getRectFromPolar(float magnitude, float angle);

#endif