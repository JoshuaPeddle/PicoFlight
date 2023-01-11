#ifndef SERVO_H
#define SERVO_H
#include <Arduino.h>
#include <Servo.h>
#include "esc.h"
#include "pins.h"

extern Servo elevator;
#ifdef DUAL_AILERON
extern Servo left_aileron;
extern Servo right_aileron;
#else
extern Servo aileron;
#endif
extern Servo rudder;


#endif