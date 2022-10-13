#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
#include "utils.h"


// Button defines
#define DELAY_BETWEEN_BUTTON_CHECKS 10
#define LONG_PRESS_MS 1000
#define NO_PRESS 0    // No button press
#define SHORT_PRESS 1 // On release < LONG_PRESS_MS
#define LONG_PRESS 2  // On release > LONG_PRESS_MS
#define HELD 4        // Held down
#define PRESS 5       // On initial press


extern unsigned long initial_press ;

extern bool bootsel_pressed;

extern unsigned long last_check; // When the last actual check of the buttons physical states was

extern int last_button_state;

int check_button();

#endif