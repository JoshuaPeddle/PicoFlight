
#pragma once
#include <Arduino.h>
#include "pins.h"
#include "algebra.h"
#include "utils.h"
#include "servos.h"
#include "ibus.h"
#include "esc.h"
#include "button.h"


//#define DEBUG
#define DEBUG_TIME // used for debugging time for loop


// 9 DOF SENSOR and AHRS

#define ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM 1
#define FILTER_UPDATE_RATE_HZ 500  //hz
#define FILTER_BETA 10.0f //ms
#define PRINT_EVERY_N_UPDATES 50

#include <Adafruit_Sensor_Calibration.h>
#include <Adafruit_AHRS.h>
#include <Adafruit_LSM9DS1.h>

// GPS
#include <GPSport.h>
#include <NMEAGPS.h>
#define DELAY_BETWEEN_GPS_CHECKS 10



extern Adafruit_Sensor *accelerometer, *gyroscope, *magnetometer;

extern Adafruit_LSM9DS1 lsm9ds1;

extern Adafruit_Sensor_Calibration_EEPROM cal;

extern struct Ibus_data ibus_data;


void setup();

void loop();

void setup_sensors();

bool init_sensors();

bool readIbus();

void calibrate();

void start_calibration_engine();

void say_hello();


void handle_ibus_update();

