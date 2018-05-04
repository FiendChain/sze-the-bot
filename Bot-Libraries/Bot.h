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
        void setLeftDistancePins(int echo, int trigger);
        void setRightDistancePins(int echo, int trigger);
        void setLinePin(int linePin);
        void setAI(Movement (*func)(float, float, int));
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
        DistanceSensor leftDistanceSensor;
        DistanceSensor rightDistanceSensor;
        LineSensor lineSensor;
        // controls
        void rotate(float angle, float magnitude);
        void move(Movement moveType);
        // control method
        void control();
};

#endif