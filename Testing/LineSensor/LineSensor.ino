#include <LineSensor.h>
const int lineSensorPin = A0;
LineSensor lineSensor(lineSensorPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  #ifdef DEBUGGING
  lineSensor.debug();
  #else
  Serial.println(lineSensor.read());
  #endif 
  delay(1000);
}
