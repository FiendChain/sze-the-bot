#include <Distance.h>
#include <stdio.h>

const int trigPin = 9;    // change pin here
const int echoPin = 10;

DistanceSensor distance;
char buffer[100];

void setup() {
  distance.setPins(echoPin, trigPin);
  Serial.begin(9600);
}

void loop() {
  snprintf(buffer, 100, "Distance: %.03f\n", distance.read());
  Serial.print(buffer);
}