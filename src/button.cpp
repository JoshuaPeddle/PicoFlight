#include "main.h"


unsigned long initial_press = 0;

bool bootsed_pressed = false; 

unsigned long last_check=0; // When the last actual check of the buttons physical states was


int last_button_state = 0;  // The last physical state of the button. Reported until last_check is exceeded and a new reading is taken.
/// @brief  Check the button state
/// @return NO_PRESS = no press, SHORT_PRESS = short press, LONG_PRESS = long press (> LONG_PRESS_MS), HELD = held, PRESS = press
int check_button(){

    if (millis() < last_check + DELAY_BETWEEN_CHECKS){
        return last_button_state;
    }
    last_check = millis();
    if (!BOOTSEL && !bootsed_pressed){
        last_button_state = NO_PRESS;
        return NO_PRESS;
    }
    if (BOOTSEL && bootsed_pressed){
        last_button_state = HELD;
        return HELD;
    }
    if (BOOTSEL && !bootsed_pressed){
        bootsed_pressed=true;
        initial_press=last_check;
        debug("PRESS");
        last_button_state = PRESS;
        return PRESS;
    }
    if (!BOOTSEL && bootsed_pressed){
        bootsed_pressed=false;
        unsigned long release=last_check;
        if (release-initial_press>LONG_PRESS_MS){
            debug("Long press");
            last_button_state = LONG_PRESS;
            return LONG_PRESS;
        }
        debug("Short press");
        last_button_state = SHORT_PRESS;
        return SHORT_PRESS;
    }

    return NO_PRESS;

}