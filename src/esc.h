
#ifndef ESC_H
#define ESC_H


#include <Servo.h>



extern Servo motor;

#define MINIMUM_SAFE_ESC_PULSE 1000
#define MAXIMUM_SAFE_ESC_PULSE 2000

#define MINIMUM_INPUT_PULSE 1000
#define MAXIMUM_INPUT_PULSE 2000


int improved_map2(int value, int minIn, int maxIn, int minOut, int maxOut);
int improved_map(int value);


class ESC
{

public:
    ESC();
    ESC(int pin);
    int set_esc_pulse(int pulse);
    void set_esc_percent(float percent);

};

extern ESC esc;

#endif