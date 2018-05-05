#ifndef _BOT_H_
#define _BOT_H_
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
        // controls
        void move(float angle, float magnitude);
        void move(Movement moveType);
        void controlJoystick();
        void getSensorData(float &, float &, int &);
        void debug();
    private:
        // bot parts
        JoystickController joystick;
        MotorController leftMotor;
        MotorController rightMotor;
        DistanceSensor leftDistanceSensor;
        DistanceSensor rightDistanceSensor;
        LineSensor lineSensor;
};

#endif