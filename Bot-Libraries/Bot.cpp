#include "Bot.h"  
#include "Arduino.h"
#include "Controls.h"

Bot::Bot()
{
    controls = Controls();
}

void Bot::update()
{
    control();
}

void Bot::debug()
{

}

void Bot::control()
{
    controls.rotate(FORWARD);
}