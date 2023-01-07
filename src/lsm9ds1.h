#pragma once

#include <utils.h>


// 9 DOF SENSOR and AHRS

#define ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM 1
#define FILTER_UPDATE_RATE_HZ 500  //hz
#define FILTER_BETA 4.5f //ms
#define PRINT_EVERY_N_UPDATES 80

#include <Adafruit_Sensor_Calibration.h>
#include <Adafruit_AHRS.h>
#include <Adafruit_LSM9DS1.h>



// 9 DOF SENSOR and AHRS
extern Adafruit_LSM9DS1 lsm9ds1;

extern Adafruit_Sensor_Calibration_EEPROM cal;





bool init_sensors(void);

void setup_sensors(void);

void start_calibration_engine();

void calibrate();