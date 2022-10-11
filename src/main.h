
#pragma once
#include <Arduino.h>
#include "pins.h"


#define DEBUG
#define DEBUG_TIME // used for debugging time for loop


#include "esc.h"
extern ESC esc;

#include <Servo.h>
extern Servo elevator;
#ifdef DUAL_AILERON
extern Servo left_aileron;
extern Servo right_aileron;
#else
Servo aileron;
#endif
extern Servo rudder;


// Button defines
#define DELAY_BETWEEN_CHECKS 100
#define LONG_PRESS_MS 1000
#define NO_PRESS 0    // No button press
#define SHORT_PRESS 1 // On release < LONG_PRESS_MS
#define LONG_PRESS 2  // On release > LONG_PRESS_MS
#define HELD 4        // Held down
#define PRESS 5       // On initial press

// IBUS receiver
#define IBUSBM_NOTIMER 1              // no timer interrupt used
#define TIME_BETWEEN_IBUS_PRINTS 1000 // How long to wait before debugging the IBUS receiver
#include <IBusBM.h>
extern IBusBM IBus;

// 9 DOF SENSOR and AHRS
#define ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM 1
#define FILTER_UPDATE_RATE_HZ 100
#include <Adafruit_Sensor_Calibration.h>
#include <Adafruit_AHRS.h>
#include <Adafruit_LSM9DS1.h>

extern Adafruit_Sensor *accelerometer, *gyroscope, *magnetometer;

extern Adafruit_LSM9DS1 lsm9ds1;

extern Adafruit_Sensor_Calibration_EEPROM cal;

struct Ibus_data
{
    uint16_t c_1 = 0;
    uint16_t c_2 = 0;
    uint16_t c_3 = 0;
    uint16_t c_4 = 0;
    uint16_t c_5 = 0;
    uint16_t c_6 = 0;
};

void setup();

void loop();

void setup_sensors();

bool init_sensors();

bool readIbus();

void calibrate();

void start_calibration_engine();

void blink(int del);

void say_hello();

int check_button();

void handle_ibus_update();

void debug(const String str);

void debug(const char *str);

void debug(int str);