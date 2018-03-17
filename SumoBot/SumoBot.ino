#include <Bot.h>

Bot bot = Bot();

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  bot.update();
  bot.debug();
  delay(1);
}
