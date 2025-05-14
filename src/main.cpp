#include "main.h"


void setup() 
{
  
}

void loop() 
{
  
}

void serialEvent(void)
{
  char command[15] = {0};
  printf("Enter command: ");
  scanf("%15s", command);

  printf("%s\n", command);
  
  parsing(command);
}