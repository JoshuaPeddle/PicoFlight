#ifndef IBUS_H
#define IBUS_H
#include <Arduino.h>
// IBUS receiver
#define IBUSBM_NOTIMER 1              // no timer interrupt used
#define TIME_BETWEEN_IBUS_PRINTS 1000 // How long to wait before debugging the IBUS receiver in ms, -1 for off
#define IBUS_LOOPS_TO_SKIP 2 // How many loops to skip before calling IBUS.loop()
#include <IBusBM.h>
#include "utils.h"
#include "pins.h"
#include "servos.h"
#include "esc.h"
#include "autopilot.h"


extern IBusBM IBus;

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
} ;


extern Ibus_data ibus_data;

bool readIbus();

bool data_updated(const Ibus_data& received, Ibus_data& old);



#endif