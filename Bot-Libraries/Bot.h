#ifndef _BOT_H_
#define _BOT_H_
#include "AI.h"
#include "Motor.h"
#include "Joystick.h"
#include "Distance.h"
#include "LineSensor.h"
#include "Movement.h"

class Bot {
    public:
        Bot();
        // set pins
        void setJoystickPins(int xPin, int yPin);
        void setLeftMotorPins(int power, int forward, int reverse);
        void setRightMotorPins(int power, int forward, int reverse);
        void setDistancePins(int echo, int trigger);
        void setLinePin(int linePin);
        // other
        void update();
        void debug();
    private:
        // bot ai
        AI ai;
        // bot parts
        JoystickController joystick;
        MotorController leftMotor;
        MotorController rightMotor;
        DistanceSensor distanceSensor;
        LineSensor lineSensor;
        // controls
        void move(Movement moveType);
        void rotate(float angle, float magnitude);
        // control method
        void control();
};

#endif