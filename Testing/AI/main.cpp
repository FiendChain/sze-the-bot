#include "AI.h"
#include "Movement.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Point {
    public:
        Point() {
            x = y = 0;
        }
        Point(float _x, float _y) {
            x = _x;
            y = _y;
        }
        float distance(Point &point) {
            float pointX = point.getX();
            float pointY = point.getY();
            float distanceSquared = pow((x-pointX), 2) + pow((y-pointY), 2);
            return pow(distanceSquared, 0.5f);
        }
        float move(float angle, float magnitude) {
            angle += M_PI/2.0f;
            float moveX = magnitude*cos(angle);
            float moveY = magnitude*sin(angle);
            x += moveX;
            y += moveY;
        }
        float getX() {
            return x;
        }
        float getY() {
            return y;
        }
        void show() {
            printf("[%.2f, %.2f]\n", x, y);
        }
    private:
        float x;
        float y;
};

int main(int argc, char *argv[]) {
    AI ai;
    Point botPos(0, 10);
    float wallY = 20;
    float botAngle = 0;

    int isInside = 1;
    const int speed = 1;
    for(int i = 0; i < 100; i++) {
        float wallX = (wallY-botPos.getY())*tan(botAngle);
        Point wallIntersect(wallX, wallY);
        float distance = botPos.distance(wallIntersect);
        ai.update(distance, isInside);
        Movement move = ai.getMove();
        switch(move) {
        case FORWARD:
            printf("Foward:");
            botPos.move(botAngle, speed);
            break;
        case BACKWARD:
            printf("Backward:");
            botPos.move(botAngle, -speed);
            break;
        case LEFT:
            printf("Left:");
            botAngle += M_PI/20.0f;
            break;
        case RIGHT:
            printf("Right:");
            botAngle -= M_PI/20.0f;
            break;
        }
        printf("(%.2f,%.2f) @ %.2frad => dist:%.2f\n", botPos.getX(), botPos.getY(), botAngle, distance);
    }

    return EXIT_SUCCESS;
}