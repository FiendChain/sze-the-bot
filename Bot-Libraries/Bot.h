#ifndef _BOT_H_
#define _BOT_H_
#include "AI.h"
#include "Controls.h" 
#include "Sensors.h"

class Bot {
    public:
        Bot();
        void update();
        Controls &getControls();
        Sensors &getSensors();
        void debug();
    private:
        AI ai;
        Controls controls;
        Sensors sensors;
        void control();
};

#endif