#ifndef _AI_H_
#define _AI_H_
#include "Movement.h"
// AI class should have a lot of internal states
// Currently just a temporary ai 
class AI {
    public:
        AI();
        void update(float, float, int);
        Movement getMove();
        void setAI(Movement (*_func)(float, float, int));
    private:
        float leftDistance;
        float rightDistance;
        int isInside;
        long long currentTime;
        Movement (*func)(float, float, int);
};

#endif