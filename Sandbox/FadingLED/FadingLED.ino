#include <freeMemory.h>

typedef enum {
  FADE_IN, FADE_OUT,
} FadeType;

// Fading light
class FadingLED {
  public:
    FadingLED(int _pin=13) {
      pin = _pin;
      value = 0;
      fadeType = FADE_IN;
      pinMode(pin, OUTPUT);
    }
    
    void update(int increment=1) {
      increment = abs(increment);
      if(fadeType == FADE_IN)
        value += increment;
      else if(fadeType == FADE_OUT)
        value -= increment;
      value = constrain(value, 0, 255);
      if(value <= 0)
        fadeType = FADE_IN;
      else if(value >= 255)
        fadeType = FADE_OUT;
      analogWrite(pin, value);
    }
  
  private:
    int pin;
    int value;
    FadeType fadeType;
};

FadingLED fadingLED;

void setup() {
  Serial.begin(9600);
  Serial.println(freeMemory());
}

void loop() {
  fadingLED.update(1);
  delay(2);
}

