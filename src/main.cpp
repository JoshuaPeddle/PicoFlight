#include "main.h"

ESC esc;

Servo elevator;
#ifdef DUAL_AILERON
Servo left_aileron;
Servo right_aileron;
#else
Servo aileron;
#endif
Servo rudder;

IBusBM IBus;

// 9 DOF SENSOR and AHRS
Adafruit_LSM9DS1 lsm9ds1 = Adafruit_LSM9DS1();

Adafruit_Sensor_Calibration_EEPROM cal;

// Adafruit_NXPSensorFusion filter; // slowest
// Adafruit_Madgwick filter;  // faster than NXP
Adafruit_Mahony filter; // fastest/smalleset

NMEAGPS gps; // This parses the GPS characters
gps_fix fix; // This holds on to the latest values

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
  delay(5000); // Delay to wait for board to stabilize
  debug("Begin setup");

  pinMode(LED_BUILTIN, OUTPUT); // Setup pins
  Serial1.setRX(IBUS_RX_PIN);

  IBus.begin(Serial1, IBUSBM_NOTIMER); // iBUS connected to Serial1 RX pin
  debug("IBus started");

  start_calibration_engine();
  debug("Calibration Engine started");

  filter.begin(FILTER_UPDATE_RATE_HZ);
  debug("Filter started");

  debug("starting lsm9ds1");
  
  Wire.setSDA(12);
  Wire.setSCL(13);
  //Wire.setClock(400000L);
  Wire.begin();
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
  elevator.attach(ELEVATOR_PIN);
#ifdef DUAL_AILERON
  left_aileron.attach(LEFT_AILERON_PIN);
  right_aileron.attach(RIGHT_AILERON_PIN);
#else
  Servo aileron.attach(AILERON_PIN);
#endif
  rudder.attach(RUDDER_PIN);

  debug("Attach ESC");
  esc = ESC(THROTTLE_PIN);
  esc.set_esc_pulse(1000);
  delay(500);

  debug("Attach GPS");
  gpsPort.begin(9600);

  timestamp = millis();
  debug("Finished setup");
  digitalWrite(LED_BUILTIN, HIGH); // Led off
}

unsigned long last_gps_check = 0; // When the last actual check of the buttons physical states was
void check_gps()
{
  unsigned long now = millis();
  if (now < last_gps_check + DELAY_BETWEEN_GPS_CHECKS)
  {
    return;
  }
  last_gps_check = now;
  while (gps.available(gpsPort))
  {
    fix = gps.read();

    debug(F("Location: "));
    if (fix.valid.location)
    {
      Serial.println(fix.latitude(), 6);
      debug(',');
      Serial.println(fix.longitude(), 6);
    }

    debug(F(", Altitude: "));
    if (fix.valid.altitude)
      debug(fix.altitude());

    debug("");
  }
}
unsigned long last_print = 0;
sensors_event_t accel, mag, gyro, temp;
void dump_pos(){

  
  if (millis() - last_print < 16.7) //60HZ
  {
    return;
  }
  lsm9ds1.getEvent(&accel, &mag, &gyro, &temp);
  last_print = millis();
  Serial.print("Accelerometer:");
  Serial.print(accel.acceleration.x);
  Serial.print(" ,  ");
  Serial.print(accel.acceleration.y);
  Serial.print(" ,  ");
  Serial.print(accel.acceleration.z);
  Serial.print("");

  Serial.print("Magnetometer:");
  Serial.print(mag.magnetic.x);
  Serial.print(" ,  ");
  Serial.print(mag.magnetic.y);
  Serial.print(" ,  ");
  Serial.print(mag.magnetic.z);
  Serial.print("");

  Serial.print("Gyroscope:");
  Serial.print(gyro.gyro.x);
  Serial.print(" ,  ");
  Serial.print(gyro.gyro.y);
  Serial.print(" ,  ");
  Serial.print(gyro.gyro.z);
  Serial.print("");

  Serial.print("Temperature:");
  Serial.print(temp.temperature);
  debug("");
}


int j = 0;
unsigned long last_time = 0;
void loop()
{
  dump_pos();
  check_gps();
  check_button(); // HELD, NO_PRESS, SHORT_PRESS, LONG_PRESS(LONG_PRESS_MS), PRESS
  if (readIbus())
  {
    // New ibus data. Update servos and esc
    handle_ibus_update();
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
