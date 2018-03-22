#ifndef _MOTOR_H_
#define _MOTOR_H_

class MotorController 
{
    public:
        MotorController();
        MotorController(int power, int forward, int reverse);
        void write(int power);
        void setPins(int power, int forward, int reverse);
        void debug();
    private:
        // pins
        int powerPin;
        int forwardPin;
        int reversePin;
        // store values for telemetry
        int powerValue;
        int forwardValue;
        int reverseValue;
};

#endif