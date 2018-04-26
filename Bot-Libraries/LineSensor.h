#ifndef _LINE_SENSOR_H_
#define _LINE_SENSOR_H_

class LineSensor {
    public:
        LineSensor();
        LineSensor(int _readPin);
        void setPin(int _readPin);
        int read();
        void debug();
    private:
        int readPin;
};

#endif