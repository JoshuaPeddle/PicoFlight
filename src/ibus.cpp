#include "main.h"
#include <IBusBM.h>


extern struct Ibus_data ibus_data;


bool data_updated(const Ibus_data& received, const Ibus_data& old)
{
  if (received.c_1 == old.c_1 && received.c_2 == old.c_2 && received.c_3 == old.c_3 && received.c_4 == old.c_4 && received.c_5 == old.c_5 && received.c_6 == old.c_6)
  {
    return false;
  }
  return true;
}

int last_ibus_print = 0;
bool readIbus()
{
  bool updated = false;
  Ibus_data new_data;
  new_data.c_1 = IBus.readChannel(0);
  new_data.c_2 = IBus.readChannel(1);
  new_data.c_3 = IBus.readChannel(2);
  new_data.c_4 = IBus.readChannel(3);
  new_data.c_5 = IBus.readChannel(4);
  new_data.c_6 = IBus.readChannel(5);

  // If the values have changed, update the struct and set the return value to true
  if (data_updated(new_data, ibus_data) == true)
  {
    ibus_data.c_1 = new_data.c_1;
    ibus_data.c_2 = new_data.c_2;
    ibus_data.c_3 = new_data.c_3;
    ibus_data.c_4 = new_data.c_4;
    ibus_data.c_5 = new_data.c_5;
    ibus_data.c_6 = new_data.c_6;
    updated = true;
  }
  if ((millis() - last_ibus_print) < TIME_BETWEEN_IBUS_PRINTS)
  {
    return updated;
  }
  debug(String("Channel 1: " + String(ibus_data.c_1)));
  debug(String("Channel 2: " + String(ibus_data.c_2)));
  debug(String("Channel 3: " + String(ibus_data.c_3)));
  debug(String("Channel 4: " + String(ibus_data.c_4)));
  debug(String("Channel 5: " + String(ibus_data.c_5)));
  debug(String("Channel 6: " + String(ibus_data.c_6)));

  last_ibus_print = millis();
  return updated;
}
