#ifndef _BOT_H_
#define _BOT_H_
#include "Arduino.h"
#include "Controls.h" 

class Bot {
    public:
        Bot();
        void update();
        void debug();
    private:
        void control();
        Controls controls;
};

#endif