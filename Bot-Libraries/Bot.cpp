#include "Bot.h"  
#include "Arduino.h"
#include "Controls.h"

Bot::Bot()
: controls(Controls())
{
    
}

void Bot::update()
{
    control();
}

void Bot::debug()
{
    controls.debug();
}

Controls &Bot::getControls()
{
    return controls;
}

void Bot::control()
{
    controls.readJoystick();
}