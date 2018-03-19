#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

class JoystickController {
  public:
    JoystickController();
    JoystickController(int _xPin, int _yPin);
    void setPins(int _xPin, int _yPin);
    void debug();
    int getX();
    int getY();
  private:
    // calibrate to a value
    void calibrateXPin(int _xBaseline);
    void calibrateYPin(int _yBaseline);
    // x pin data
    int xPin;
    int xBaseline;
    float xScalePositive;
    float xScaleNegative;
    // y pin data
    int yPin;
    int yBaseline;
    float yScalePositive;
    float yScaleNegative;
};

#endif