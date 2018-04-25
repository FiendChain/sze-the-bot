#ifndef _DISTANCE_H_
#define _DISTANCE_H_

class DistanceSensor {
    public:
        DistanceSensor();
        DistanceSensor(int _echoPin, int _triggerPin);
        void setPins(int _echoPin, int _triggerPin);
        float read();
        void debug();
    private:
        int echoPin;
        int triggerPin;
};

#endif