#ifndef _AI_H_
#define _AI_H_
#include "Movement.h"
#include <stdlib.h>
#include <vector>
// AI class should have a lot of internal states
// Currently just a temporary ai 
class AI {
    public:
        AI();
        void update(float dt, std::vector<float> _distances, int _isInside); 
        Movement getMove();
        Movement (*funcPtr)(AI &);
        void setFunctionPointer(Movement (*_funcPtr)(AI &));
        // variable (public so sub classes can modify)
        std::vector<float> distances;
        int isInside;
        float currentTime;  // milliseconds
};

#endif