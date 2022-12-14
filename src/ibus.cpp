#include "ibus.h"


IBusBM IBus;


struct Ibus_data 
{
    uint16_t c_1 = 1500;
    uint16_t c_2 = 1500;
    uint16_t c_3 = 1000;
    uint16_t c_4 = 1500;
    uint16_t c_5 = 1500;
    uint16_t c_6 = 1500;
    int get_channel_value(int channel)
    {
        switch (channel)
        {
        case 1:
            return this->c_1;
            break;
        case 2:
            return this->c_2;
            break;
        case 3:
            return this->c_3;
            break;
        case 4:
            return this->c_4;
            break;
        case 5:
            return this->c_5;
            break;
        case 6:
            return this->c_6;
            break;
        default:
            return 0;
            break;
        }
    };
} ibus_data;



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
  if (new_data.c_1 == 0 || new_data.c_2 == 0 || new_data.c_3 == 0 || new_data.c_4 == 0 || new_data.c_5 == 0 || new_data.c_6 == 0)
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

  last_ibus_print = millis();
  return updated;
}


void handle_ibus_update()
{
    //debug("IBUS updated");
    elevator.writeMicroseconds(ibus_data.get_channel_value(ELEVATOR_IBUS_CHANNEL));
#ifdef DUAL_AILERON
    left_aileron.writeMicroseconds(ibus_data.get_channel_value(LEFT_AILERON_IBUS_CHANNEL) + roll_offset);
    right_aileron.writeMicroseconds(ibus_data.get_channel_value(RIGHT_AILERON_IBUS_CHANNEL) - roll_offset);
    //Serial.println(ibus_data.get_channel_value(RIGHT_AILERON_IBUS_CHANNEL) + roll_offset);
#else
    aileron.writeMicroseconds(ibus_data.get_channel_value(AILERON_IBUS_CHANNEL));
#endif
    rudder.writeMicroseconds(ibus_data.get_channel_value(RUDDER_IBUS_CHANNEL));

    esc.set_esc_pulse(ibus_data.get_channel_value(THROTTLE_IBUS_CHANNEL));
    //debug(res);
    //debug(ibus_data.get_channel_value(THROTTLE_IBUS_CHANNEL));
}