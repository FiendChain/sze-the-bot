#include "Arduino.h"
#include "Bot.h"  
#include "Constants.h"

Bot::Bot() {
    
}

// update the bot
void Bot::update() {
    control();
}

// control the bot
// JOYSTICK = read joystick
// AI = update sensor, pass sensor data to AI, get AI output to controls
void Bot::control() {
    #if CONTROL_TYPE == 0
    float angle = joystick.getAngle();
    int magnitude = joystick.getMagnitude();
    rotate(angle, magnitude);
    #elif CONTROL_TYPE == 1
    float distance = distanceSensor.read();
    int isInside = lineSensor.read();
    ai.update(distance, isInside); 
    Movement moveType = ai.getMove();
    move(moveType); 
    #else
    #warning No movement type for bot was chosen
    #endif
}