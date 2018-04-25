#ifndef _SENSORS_H_
#define _SENSORS_H_
#include "Distance.h"
#include "LineSensor.h"

class Sensors {
    public:
        Sensors();
        void setDistancePins(int _echoPin, int _triggerPin);
        void setLinePin(int _linePin);
        float getDistance();
        int checkInside();
    private:
        DistanceSensor distance;
        LineSensor line;
};

#endif