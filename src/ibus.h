#ifndef IBUS_H
#define IBUS_H
#include <Arduino.h>
// IBUS receiver
#define IBUSBM_NOTIMER 1              // no timer interrupt used
#define TIME_BETWEEN_IBUS_PRINTS 10 // How long to wait before debugging the IBUS receiver in ms, -1 for off
#include <IBusBM.h>
#include "utils.h"
#include "pins.h"
#include "servos.h"
#include "esc.h"
#include "autopilot.h"


extern IBusBM IBus;

extern struct Ibus_data ibus_data;


bool readIbus();

bool data_updated(const Ibus_data& received, const Ibus_data& old);

void handle_ibus_update();

#endif