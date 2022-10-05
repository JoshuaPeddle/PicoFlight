#include "main.h"


int last_ibus_print = 0;
void readIbus()
{
  if ((millis() - last_ibus_print) < TIME_BETWEEN_IBUS_PRINTS)
  {
    return;
  }
  int val;
  val = IBus.readChannel(0);
  debug(String("Channel 1: " + String(val)));
  val = IBus.readChannel(1);
  debug(String("Channel 2: " + String(val)));
  val = IBus.readChannel(2);
  debug(String("Channel 3: " + String(val)));
  val = IBus.readChannel(3);
  debug(String("Channel 4: " + String(val)));
  val = IBus.readChannel(4);
  debug(String("Channel 5: " + String(val)));
  val = IBus.readChannel(5);
  debug(String("Channel 6: " + String(val)));
  last_ibus_print = millis();
}
