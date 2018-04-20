#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

class JoystickController {
  public:
    JoystickController();
    JoystickController(int _xPin, int _yPin);
    void setPins(int _xPin, int _yPin);
    void debug();
    // cartesian
    int getX();
    int getY();
    // polar
    int getMagnitude();
    float getAngle();
  private:
    // calibrate to a value
    void calibrateXPin(int _xBaseline);
    void calibrateYPin(int _yBaseline);
    // x pin data
    int xPin;
    int xBaseline;
    float xScale;
    // y pin data
    int yPin;
    int yBaseline;
    float yScale;
};

#endif