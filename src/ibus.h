#ifndef IBUS_H
#define IBUS_H
#include <Arduino.h>
// IBUS receiver
#define IBUSBM_NOTIMER 1              // no timer interrupt used
#define TIME_BETWEEN_IBUS_PRINTS 1000 // How long to wait before debugging the IBUS receiver
#include <IBusBM.h>
#include "utils.h"
#include "pins.h"
#include "servos.h"
#include "esc.h"



extern IBusBM IBus;

extern struct Ibus_data ibus_data;



#endif