#include <Arduino.h>
#include "utils.h"
#include "main.h"


void debug(String str)
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


void blink()
{
  int del = 1001;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(del);
  digitalWrite(LED_BUILTIN, LOW);
  delay(del);
}