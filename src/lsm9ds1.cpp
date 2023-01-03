#include "main.h"

Adafruit_Sensor *accelerometer, *gyroscope, *magnetometer;

bool init_sensors(void)
{
  if (!lsm9ds1.begin())
  {
    return false;
  }
  delay(100);
  accelerometer = &lsm9ds1.getAccel();
  gyroscope = &lsm9ds1.getGyro();
  magnetometer = &lsm9ds1.getMag();

  return true;
}

void setup_sensors(void)
{
  // set lowest range
  lsm9ds1.setupAccel(lsm9ds1.LSM9DS1_ACCELRANGE_2G);
  lsm9ds1.setupMag(lsm9ds1.LSM9DS1_MAGGAIN_4GAUSS);
  lsm9ds1.setupGyro(lsm9ds1.LSM9DS1_GYROSCALE_245DPS);
}

void start_calibration_engine()
{
  Serial.println("Calibration filesys test");
  if (!cal.begin())
  {
    Serial.println("Failed to initialize calibration helper");
    while (1)
      yield();
  }
  if (!cal.loadCalibration())
  {
    Serial.println("No calibration loaded/found... will start calibration");
    calibrate();
  }
  else
  {
    Serial.println("Loaded existing calibration");
  }
}

void calibrate()
{
  Serial.println("**WARNING** Fake calibration");
  cal.accel_zerog[0] = 0;
  cal.accel_zerog[1] = 0;
  cal.accel_zerog[2] = 0;

  cal.gyro_zerorate[0] = 0;
  cal.gyro_zerorate[1] = 0;
  cal.gyro_zerorate[2] = 0;

  cal.mag_hardiron[0] = 0;
  cal.mag_hardiron[1] = 0;
  cal.mag_hardiron[2] = 0;

  cal.mag_field = 0;

  cal.mag_softiron[0] = 0;
  cal.mag_softiron[1] = 0;
  cal.mag_softiron[2] = 0;
  cal.mag_softiron[3] = 0;
  cal.mag_softiron[4] = 0;
  cal.mag_softiron[5] = 0;
  cal.mag_softiron[6] = 0;
  cal.mag_softiron[7] = 0;
  cal.mag_softiron[8] = 0;
  if (!cal.saveCalibration())
  {
    Serial.println("**WARNING** Couldn't save calibration");
  }
  else
  {
    Serial.println("Wrote calibration");
  }
  cal.printSavedCalibration();
}