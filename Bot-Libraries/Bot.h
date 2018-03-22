#ifndef _BOT_H_
#define _BOT_H_
#include "Controls.h" 

class Bot 
{
    public:
        Bot();
        void update();
        void debug();
        Controls &getControls();
    private:
        void control();
        Controls controls;
};

#endif