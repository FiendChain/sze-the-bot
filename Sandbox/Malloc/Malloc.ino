// #include <stdlib.h>
#include <freeMemory.h>

#define TOTAL_BYTES 1000

void debugMemory()
{
  Serial.print("Total free memory: ");
  Serial.print(freeMemory()); 
  Serial.println("bytes");
}

void runTest()
{
  Serial.println(F("<< Begin >>"));
  debugMemory();
  char *mem = (char *)malloc(TOTAL_BYTES*sizeof(char));
  if(mem != NULL) {
    Serial.println("<Malloc>");
    debugMemory();
    free(mem);
    Serial.println("<Free>");
    debugMemory();
  } else {
    Serial.println("<Failed to malloc>");
  }
}

void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < 100; i++)
    runTest();
}

void loop()
{
  
}


