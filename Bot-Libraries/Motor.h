#ifndef _MOTOR_H_
#define _MOTOR_H_

class MotorController {
    public:
        MotorController();
        MotorController(int _powerPin, int _forwardPin, int _reversePin);
        void write(int power);
        void setPins(int _powerPin, int _forwardPin, int _reversePin);
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