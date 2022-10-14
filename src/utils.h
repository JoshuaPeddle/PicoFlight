#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include "pins.h"

void debug(const char *str);

void debug(String str);

void debug(int str);

void blink(int del);

void say_hello();
#endif