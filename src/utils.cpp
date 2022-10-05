#include "utils.h"
#include "main.h"

void debug(const String str)
{
#ifdef DEBUG
  Serial.println(str);
#endif
}

void debug(const char *str)
{
#ifdef DEBUG
  Serial.println(str);
#endif
}

void debug(int str)
{
#ifdef DEBUG
  Serial.println(str);
#endif
}


void blink(int del)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(del);
  digitalWrite(LED_BUILTIN, LOW);
  delay(del);
}

void say_hello()
{
  debug("Hello World!");
}