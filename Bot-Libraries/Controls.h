 #ifndef _CONTROLS_H_
#define _CONTROLS_H_

typedef enum {
    LEFT, RIGHT, FORWARD, BACKWARD,
} Direction;

class Controls {
    public:
        Controls();
        // motors
        void setMotorPins(int left, int right);
        void writeMotor(int left, int right);
        void rotate(Direction dir);
    private:
        int leftMotorPin, rightMotorPin;
};

#endif