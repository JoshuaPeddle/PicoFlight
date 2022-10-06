#include "main.h"

Servo servo_0;
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;

IBusBM IBus;
Ibus_data ibus_data;
// 9 DOF SENSOR and AHRS
Adafruit_LSM9DS1 lsm9ds1 = Adafruit_LSM9DS1();

Adafruit_Sensor_Calibration_EEPROM cal;

// Adafruit_NXPSensorFusion filter; // slowest
// Adafruit_Madgwick filter;  // faster than NXP
Adafruit_Mahony filter; // fastest/smalleset

uint32_t timestamp;
void setup()
{
  Serial.begin(115200);
#ifdef DEBUG
  while (!Serial)
  {
    delay(10);
  }
#endif
  delay(1000); // Delay to wait for board to stabilize
  debug("Begin setup");

  pinMode(LED_BUILTIN, OUTPUT); // Setup pins

  Serial1.setRX(1);

  IBus.begin(Serial1, IBUSBM_NOTIMER); // iBUS connected to Serial1 RX pin
  debug("IBus started");

  start_calibration_engine();
  debug("Calibration Engine started");

  filter.begin(FILTER_UPDATE_RATE_HZ);
  debug("Filter started");

  debug("starting lsm9ds1");
  if (init_sensors())
  {
    setup_sensors();
    debug("lsm9ds1 started");
  }
  else
  {
    debug("lsm9ds1 failed to start");
  }

  debug("Attch servos");
  servo_0.attach(2);  // attaches the servo on GIO2 to the servo object
  servo_1.attach(4);  // attaches the servo on GIO2 to the servo object
  servo_2.attach(6);  // attaches the servo on GIO2 to the servo object
  servo_3.attach(8);  // attaches the servo on GIO2 to the servo object
  servo_3.attach(10); // attaches the servo on GIO2 to the servo object

  timestamp = millis();
  debug("Finished setup");
}

int j = 0;
unsigned long last_time = 0;
void loop()
{
  check_button(); // HELD, NO_PRESS, SHORT_PRESS, LONG_PRESS(LONG_PRESS_MS), PRESS
  if (readIbus())
  {
    // New ibus data. Update servos.
    update_servo_positions();
  }

  IBus.loop(); // Must be called once a loop

#ifdef DEBUG_TIME
  if (millis() > last_time + 1000)
  {
    last_time = millis();
    debug((int)(j / 1000));
    j = 0;
  }
  else
  {
    j++;
  }
#endif
}

void update_servo_positions()
{
  // debug("Updating servo positions");
  servo_0.write(ibus_data.c_1);
  servo_1.write(ibus_data.c_2);
  servo_2.write(ibus_data.c_3);
  servo_3.write(ibus_data.c_4);
  servo_4.write(ibus_data.c_5);
  servo_5.write(ibus_data.c_6);
}