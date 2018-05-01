#define _USE_MATH_DEFINES
#include "Angles.h"
#include <math.h>

// compute distance for an angle
float absFloat(float value) {
    return value > 0 ? value : -value;
}

float absFloat(sf::Vector2f &v) {
    return pow(v.x*v.x + v.y*v.y, 0.5f);
}

// constrain an angle
float constrainAngle(float angle) {
    while(angle > M_PI) {
        angle -= 2*M_PI;
    }
    while(angle < -M_PI) {
        angle += 2*M_PI;
    }
    return angle;
}

// get angle of vector
float getAngle(float x, float y) { 
    float angle = 0; 
    // all directions except 0, PI/2, PI, 1.5PI
    if(y != 0 && x != 0) {
        float absRatio = absFloat(x)/absFloat(y);
        float absAngle = atan(absRatio);
        // top right
        if(y > 0 && x > 0)
            angle = -absAngle;
        // bottom right
        else if(y < 0 && x > 0)
            angle = -M_PI + absAngle;
        // bottom left
        else if(y < 0 && x < 0)
            angle = M_PI - absAngle;
        // top left
        else if(y > 0 && x < 0)
            angle = absAngle;
    // forward and back
    } else if(y != 0) {
        angle = (y > 0) ? 0 : M_PI;
    // left and right
    } else if(x != 0) {
        angle = (x > 0) ? -0.5*M_PI : +0.5*M_PI;
    // no input
    } else {
        angle = 0;
    }
    return angle;
}

// get vector from polar coordinates
sf::Vector2f getRectFromPolar(float magnitude, float angle) {
    angle = M_PI/2.0f + angle;
    float x = magnitude * cos(angle);
    float y = magnitude * sin(angle);
    sf::Vector2f vector(x, y);
    return vector;
}
