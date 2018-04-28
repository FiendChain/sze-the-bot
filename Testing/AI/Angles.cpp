#include "Angles.h"
#define _USE_MATH_DEFINES
#include <math.h>

// compute distance for an angle
float absFloat(float value) {
    return value > 0 ? value : -value;
}

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