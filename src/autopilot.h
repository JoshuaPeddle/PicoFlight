#pragma once
#include "utils.h"
#include "pins.h"
#include "ibus.h"
#include "lsm9ds1.h"

#define AUTO_LEVEL_ALPHA 10

// Number of values to average for auto leveling
#define AUTO_LEVELING_SMOOTHING 3

extern bool auto_leveling;
extern int roll_offset;


void update_filter();

void auto_level();

