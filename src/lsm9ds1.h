#ifndef LSM9DS1_H
#define LSM9DS1_H


// 9 DOF SENSOR and AHRS
#define ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM 1
#define FILTER_UPDATE_RATE_HZ 100
#include <Adafruit_Sensor_Calibration.h>
#include <Adafruit_AHRS.h>
#include <Adafruit_LSM9DS1.h>


extern Adafruit_Sensor *accelerometer, *gyroscope, *magnetometer;

// 9 DOF SENSOR and AHRS
extern Adafruit_LSM9DS1 lsm9ds1;// = Adafruit_LSM9DS1();

extern Adafruit_Sensor_Calibration_EEPROM cal;

void setup_sensors();

bool init_sensors();

void calibrate();

void start_calibration_engine();
#endif