#include "Arduino.h"  
#include "Constants.h"
#include "Distance.h"

DistanceSensor::DistanceSensor() {
    setPins(UNKNOWN_PIN, UNKNOWN_PIN);
}

DistanceSensor::DistanceSensor(int _echoPin, int _triggerPin) {
    setPins(_echoPin, _triggerPin);
}

// set the pins for distance sensor
void DistanceSensor::setPins(int _echoPin, int _triggerPin) {
    echoPin = _echoPin;
    triggerPin = _triggerPin;
    if(echoPin != UNKNOWN_PIN && triggerPin != UNKNOWN_PIN) {
        pinMode(echoPin, INPUT);
        pinMode(triggerPin, OUTPUT); 
    }
}

// read the sensor
float DistanceSensor::read() {
    if(echoPin == UNKNOWN_PIN || triggerPin == UNKNOWN_PIN) {
        return 0;
    }
    // send sound wave
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    // get time taken for sound pulse to return
    // pulseIn is in milliseconds
    // convert to seconds
    float echoTime = pulseIn(echoPin, HIGH)/1000.0f; 
    // convert echoTime to distance
    // distance = (speed * time) / 2 (halve distance since it goes forward and back)
    // since speed = m/s, time = s, distance = m
    // convert distance into centimetres
    float distance = (SPEED_SOUND*echoTime)/2.0f;
    distance /= 10.0f;
    return distance;  
}
