#include <Arduino.h>

// IBUS communication
#include <IBusBM.h>
#define IBUSBM_NOTIMER 1 // no timer interrupt used
IBusBM IBus; // IBus object



// 9 DOF SENSOR
#include <Adafruit_Sensor_Calibration.h>
#include <Adafruit_AHRS.h>

Adafruit_Sensor *accelerometer, *gyroscope, *magnetometer;
#include <Adafruit_LSM9DS1.h>
Adafruit_LSM9DS1 lsm9ds1 = Adafruit_LSM9DS1();

bool init_sensors(void) {
  if (!lsm9ds1.begin()) {
    return false;
  }
  accelerometer = &lsm9ds1.getAccel();
  gyroscope = &lsm9ds1.getGyro();
  magnetometer = &lsm9ds1.getMag();

  return true;
}

void setup_sensors(void) {
  // set lowest range
  lsm9ds1.setupAccel(lsm9ds1.LSM9DS1_ACCELRANGE_2G);
  lsm9ds1.setupMag(lsm9ds1.LSM9DS1_MAGGAIN_4GAUSS);
  lsm9ds1.setupGyro(lsm9ds1.LSM9DS1_GYROSCALE_245DPS);
}

Adafruit_LSM9DS1 lsm9ds = Adafruit_LSM9DS1();

//Adafruit_NXPSensorFusion filter; // slowest
//Adafruit_Madgwick filter;  // faster than NXP
Adafruit_Mahony filter;  // fastest/smalleset






void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  IBus.begin(Serial1, IBUSBM_NOTIMER);    // iBUS object connected to serial0 RX pin
}

void blink() {
  int del = 1001;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(del);
  digitalWrite(LED_BUILTIN, LOW);
  delay(del);
}

void loop() {
  blink();

  IBus.loop();
  int val;
  val = IBus.readChannel(0); // get latest value for servo channel 1
}