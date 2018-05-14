#define _USE_MATH_DEFINES
#include <math.h>
#include <Movement.h>

void update_ai() {  
  // persistance
  static long long prevTime = 0;
  static int isAvoid = 0;
  static int i = 0;
  // always updating
  long long currentTime = millis();
  float leftDistance = 0, rightDistance = 0;
  int isOutside = 0;
  bot.getSensorData(leftDistance, rightDistance, isOutside);
  // avoid falling off
  if(isAvoid) {
    if(currentTime-prevTime > 2000) {
      isAvoid = 0;
      bot.move(FORWARD);
      return;
    } else {
      bot.move(255, M_PI*0.75f);   
      return;
    }
  }
  
  if(isOutside) {
    prevTime = millis();
    isAvoid = 1;
    bot.move(BACKWARD);
    return;
  }
  
  bot.move(FORWARD); 
  return;
}
