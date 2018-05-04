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
    float leftDistance = leftDistanceSensor.read();
    float rightDistance = rightDistanceSensor.read();
    int isInside = lineSensor.read();
    ai.update(leftDistance, rightDistance, isInside); 
    Movement moveType = ai.getMove();
    move(moveType); 
    #else
    #warning No movement type for bot was chosen
    #endif
}

// give ai a function to call
void Bot::setAI(Movement (*func)(float, float, int)) {
    ai.setAI(func);
}