
#pragma once
#include <Arduino.h>
#include "pins.h"
#include "algebra.h"
#include "utils.h"
#include "servos.h"
#include "ibus.h"
#include "esc.h"
#include "button.h"
#include "lsm9ds1.h"
#include "autopilot.h"


#define DEBUG
#define DEBUG_TIME // used for debugging time for loop


// GPS
#include <GPSport.h>
#include <NMEAGPS.h>
#define DELAY_BETWEEN_GPS_CHECKS 10





//extern Adafruit_LSM9DS1 lsm9ds1;

//extern Adafruit_Sensor_Calibration_EEPROM cal;

//extern struct Ibus_data ibus_data;


void setup();

void loop();

void auto_level();

void handle_button_press(int press);



