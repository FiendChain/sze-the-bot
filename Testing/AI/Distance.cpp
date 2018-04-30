#include "Distance.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdarg.h>
#include "Angles.h"

DistanceSensor::DistanceSensor(float _fovAngle, float _maxRange, float _fovPoints) 
:   fovAngle(_fovAngle),
    maxRange(_maxRange),
    fovPoints(_fovPoints),
    fov(_fovPoints+2)
{
    // init fov points
    for(sf::Vertex &v: fov) {
        v.position.x = v.position.y = 0;
        v.color = sf::Color::White;
    }
}

// set and get location of sensor
void DistanceSensor::setPosition(sf::Vector2f _position) {
    position = _position;
}

void DistanceSensor::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

sf::Vector2f DistanceSensor::getPosition() {
    return position;
}

// render the sensor's fov field
void DistanceSensor::render(sf::RenderWindow &window) {
    window.draw(fov.data(), fov.size(), sf::LinesStrip);
}

// compute fov array
// the fov array is made up of a discrete number of points
// each point's distance is calculated, and stored
// get nearest distance and return
float DistanceSensor::getDistance(float angle, std::vector<Entity> &objects) {
    float currAngle = angle + fovAngle/2.0f;
    float increment = fovAngle/(float)(fovPoints-1);
    float closestDistance = maxRange;
    for(int i = 0, size = fov.size(); i < size; i++) {
        sf::Vertex &v = fov.at(i);
        if(i == 0 || i == size-1) {
            v.position = position;
        } else {
            float distance = readAngle(constrainAngle(currAngle), objects);
            if(distance < closestDistance) {
                closestDistance = distance;
            }
            v.position = getRectFromPolar(distance, currAngle) + position;
            currAngle -= increment;
        }
    }
    // updateText(7, 0, 10, "Distance:%.0f", closestDistance); // debug text
    return closestDistance;
}

// check if angle intersect at correct quadrant
// ie. if the FOV scanline points in the opposite direction of the object, 
// but the equation for the scan line still intersects the object, 
// return 0 to prevent detection of objects behind the scanline's direction
int DistanceSensor::checkAngle(float angle, Entity &object) {
    sf::Vector2f diffPos = object.getPosition()-position;
    float angleDiff = getAngle(diffPos.x, diffPos.y);
    float absAngleDiff = absFloat(angle-angleDiff);
    if(absAngleDiff >= M_PI/2.0f && absAngleDiff <= 1.5*M_PI) {
        return 0;
    }
    return 1;
}

// gets nearest distance, at a particular angle
float DistanceSensor::readAngle(float angle, std::vector<Entity> &objects) {
    float closestDistance = maxRange;
    for(Entity &e: objects) {
         // ignore if sensor is inside entity
        sf::Vector2f posDiff = position-e.getPosition();
        float R = e.getSize();
        if(absFloat(posDiff.x) < R && absFloat(posDiff.y) < R) {
            continue;
        }
        // otherwise try to get distance
        float distance = getDistanceEntity(angle, e);
        if(distance < closestDistance) {
            closestDistance = distance;
        }
    }
    return closestDistance;
}

float DistanceSensor::getDistanceEntity(float angle, Entity &e) {
    float distance = maxRange;
    // ignore if entity not within angular range
    angle = constrainAngle(angle);
    if(!checkAngle(angle, e)) return distance; 
    // get distance
    const float angleRange = 0.02;
    float absAngle = absFloat(angle);
    if((absAngle <= angleRange && absAngle >= -angleRange) || (absAngle <= M_PI+angleRange && absAngle >= M_PI-angleRange)) {
        distance = getVerticalDistance(e);
    } else {
        // get line equation
        float m = tan(angle+(M_PI/2.0f));
        float b = position.y-(m*position.x);
        distance = getNonVerticalDistance(m, b, e);
    }
    return distance;
}

// for vertical, get y intercept
// circle is (x-xo)^2 + (y-y0)^2 = r^2
// for y int:
// (y-y0)^2 = r^2 - (x-x0)^2
// y = -+sqrt(r^2 - (x-x0)^2) + y0
// distance = |ycurr - y|
float DistanceSensor::getVerticalDistance(Entity &e) {
    float distance = maxRange;
    sf::Vector2f ePos = e.getPosition();
    float R = e.getSize();
    // if intercept is possible, compute
    float A = pow(R,2) - pow(position.x-ePos.x,2);
    if(A < 0) return distance; // out of range
    float A_sqrt = pow(A, 0.5f);
    // get distance A
    float yInt_Pos = A_sqrt + ePos.y;
    float dist_A = absFloat(position.y-yInt_Pos);
    // get distance B
    float yInt_Neg = -A_sqrt + ePos.y;
    float dist_B = absFloat(position.y-yInt_Neg);
    // fetch smallest distance
    distance = (dist_A < dist_B) ? dist_A : dist_B;
    return distance;
}

// for other get equ of line first
// y = mx+b
// m = tan(angle+PI/2)
// since b = y-mx, sub y and x
// then check if there is intercept with circle equation
// sub in y = mx+b into (x-xo)^2 + (y-y0)^2 = r^2:
// expanding, x^2(m^2+1) + x(-2x0 + 2km) + (x0^2+k^2-r^2) = 0, where k = b-y0
// check the discriminant if there is intercept, then solve
// x_intercept = (-b + delta) / 2a = (-(-2x0+2km)) 
float DistanceSensor::getNonVerticalDistance(float m, float b, Entity &e) {
    float distance = maxRange;
    sf::Vector2f ePos = e.getPosition();
    float R = e.getSize();
    float k = b-ePos.y;
    float A = pow(m,2) + 1;
    float B = -2*ePos.x + 2*k*m;
    float C = pow(ePos.x,2) + pow(k,2) - pow(R,2);
    // check if intercept: delta = b^2 - 4ac = (-2x0+2km)^2 - 4(m^2+1)(x0^2+k^2-r^2)
    // get  x^2(m^2+1) + x(-2x0 + 2km) + (x0^2+k^2-r^2) = 0, where k = b-y0 into Ax^2 + Bx^2 + C = 0
    float delta = pow(B,2) - 4*A*C;
    if(delta < 0) return distance;   // no intercept
    float delta_sqrt = pow(delta,0.5f);
    // get distance A
    float x_int_A = (-B-delta_sqrt)/(2.0f*A);
    float y_int_A = m*x_int_A + b;
    float distanceA_squared = pow(position.x-x_int_A,2) + pow(position.y-y_int_A,2);
    float distanceA = pow(distanceA_squared,0.5f);
    // get distance B
    float x_int_B = (-B+delta_sqrt)/(2.0f*A);
    float y_int_B = m*x_int_B + b;
    float distanceB_squared = pow(position.x-x_int_B,2) + pow(position.y-y_int_B,2);
    float distanceB = pow(distanceB_squared,0.5f);
    // get cloest distance
    distance = (distanceA < distanceB) ? distanceA : distanceB;
    return distance;
} 