#ifndef _AI_H_
#define _AI_H_
#include "Movement.h"
// AI class should have a lot of internal states
// Currently just a temporary ai 
class AI {
    public:
        AI();
        void update(float dt, float _distance, int _isInside);
        Movement getMove();
    private:
        float distance;
        int isInside;
        float currentTime;  // milliseconds
};

#endif