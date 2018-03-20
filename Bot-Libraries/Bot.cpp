#include "Arduino.h"
#include "Bot.h"  
#include "Constants.h"
#include "Controls.h"

Bot::Bot()
{
    
}

void Bot::update()
{
    control();
}

Controls &Bot::getControls()
{
    return controls;
}

void Bot::control()
{
    #ifdef USE_JOYSTICK
    controls.readJoystick();
    #endif
}