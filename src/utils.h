#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>

void debug(const char *str);

void debug(String str);

void debug(int str);

void blink(int del);

void say_hello();

void python_debug();
#endif