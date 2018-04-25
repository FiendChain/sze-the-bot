#include "Arduino.h"
#include "Bot.h"  
#include "Constants.h"

Bot::Bot() {
    
}

// update the bot
void Bot::update() {
    control();
}

// return reference to the bot's controls
// use this to configure the controller class for pins
Controls &Bot::getControls() {
    return controls;
}

// return reference to bot's sensors
// use this to configure the sensor pins
Sensors &Bot::getSensors() {
    return sensors;
}

// control the bot
// JOYSTICK = read joystick
// AI = update sensor, pass sensor data to AI, get AI output to controls
void Bot::control() {
    // control via joystick
    // controls.readJoystick();

    // simple ai
    float distance = sensors.getDistance();
    int isInside = sensors.checkInside();
    ai.update(distance, isInside); 
    Movement move = ai.getMove();
    controls.move(move);
}