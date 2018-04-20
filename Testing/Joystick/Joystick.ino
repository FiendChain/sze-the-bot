#include <stdio.h>
#include <Joystick.h>

int xaxis = A0;
int yaxis = A1;
char buffer[100] = {0};

JoystickController joystick;

void setup()
{
  //pinMode(xaxis, INPUT);
  //pinMode(yaxis, INPUT);
  Serial.begin(9600);
  joystick.setPins(xaxis, yaxis);
}

void loop()
{
  //rawTest();
  classTest();
}

void rawTest()
{
  int xval = analogRead(xaxis);
  int yval = analogRead(yaxis);
  
  snprintf(buffer, 100, "x:%d y:%d", xval, yval);
  Serial.println(buffer);
}

void classTest()
{
  joystick.debug();
  delay(1000);
}
