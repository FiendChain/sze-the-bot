#include "Arduino.h"
#include "Bot.h"  
#include "Constants.h"

Bot::Bot() {
    
}

// control the bot
// JOYSTICK = read joystick
// AI = update sensor, pass sensor data to AI, get AI output to controls
void Bot::controlJoystick() {
    float angle = joystick.getAngle();
    int magnitude = joystick.getMagnitude();
    move(angle, magnitude);
}