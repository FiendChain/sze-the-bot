#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include "Joystick.h"
#include "Motor.h"

typedef enum {
    FORWARD, BACKWARD, LEFT, RIGHT, STOP
} Movement;

class Controls {
    public:
        Controls();
        // motors
        void move(Movement move);   
        void rotate(float angle, float magnitude);
        void setLeftMotorPins(int power, int forward, int reverse);
        void setRightMotorPins(int power, int forward, int reverse);
        // joystick
        void setJoystickPins(int xPin, int yPin);
        void readJoystick();
        void debug();
    private:    
        MotorController leftMotor;
        MotorController rightMotor; 
        JoystickController joystick;
};

#endif