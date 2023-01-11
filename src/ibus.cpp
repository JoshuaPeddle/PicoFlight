#include "ibus.h"


IBusBM IBus;



Ibus_data ibus_data;

bool data_updated(const Ibus_data& received, Ibus_data& old)
{
  if (received.c_1 == old.c_1 && received.c_2 == old.c_2 && received.c_3 == old.c_3 && received.c_4 == old.c_4 && received.c_5 == old.c_5 && received.c_6 == old.c_6 && received.c_7 == old.c_7 && received.c_8 == old.c_8 && received.c_9 == old.c_9 && received.c_10 == old.c_10 )
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
  new_data.c_7 = IBus.readChannel(6);
  new_data.c_8 = IBus.readChannel(7);
  new_data.c_9 = IBus.readChannel(8);
  new_data.c_10 = IBus.readChannel(9);
  if (new_data.c_1 == 0 && new_data.c_2 == 0 && new_data.c_3 == 0 && new_data.c_4 == 0 && new_data.c_5 == 0 && new_data.c_6 == 0 && new_data.c_7 == 0 && new_data.c_8 == 0 && new_data.c_9 == 0 && new_data.c_10 == 0)
  {
    return false;
  }

  // If the values have changed, update the struct and set the return value to true
  if (data_updated(new_data, ibus_data) == true)
  {
    ibus_data.c_1 = new_data.c_1;
    ibus_data.c_2 = new_data.c_2;
    ibus_data.c_3 = new_data.c_3;
    ibus_data.c_4 = new_data.c_4;
    ibus_data.c_5 = new_data.c_5;
    ibus_data.c_6 = new_data.c_6;
    ibus_data.c_7 = new_data.c_7;
    ibus_data.c_8 = new_data.c_8;
    ibus_data.c_9 = new_data.c_9;
    ibus_data.c_10 = new_data.c_10;
    updated = true;
  }
  if ((int)(millis() - last_ibus_print) < TIME_BETWEEN_IBUS_PRINTS || TIME_BETWEEN_IBUS_PRINTS == -1)
  {
    return updated;
  }
  debug(String("Channel 1: " + String(ibus_data.c_1)));
  debug(String("Channel 2: " + String(ibus_data.c_2)));
  debug(String("Channel 3: " + String(ibus_data.c_3)));
  debug(String("Channel 4: " + String(ibus_data.c_4)));
  debug(String("Channel 5: " + String(ibus_data.c_5)));
  debug(String("Channel 6: " + String(ibus_data.c_6)));
  debug(String("Channel 7: " + String(ibus_data.c_7)));
  debug(String("Channel 8: " + String(ibus_data.c_8)));
  debug(String("Channel 9: " + String(ibus_data.c_9)));
  debug(String("Channel 10: " + String(ibus_data.c_10)));

  last_ibus_print = millis();
  return updated;
}


