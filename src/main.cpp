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



//Adafruit_NXPSensorFusion filter; // slowest
Adafruit_Madgwick filter;  // faster than NXP
//Adafruit_Mahony filter; // fastest/smalleset

NMEAGPS gps; // This parses the GPS characters
gps_fix fix; // This holds on to the latest values


// This function prints a specifically formatted version of the state of the ststem.
// This is read by the various python tools available 
void python_debug()
{
  // 
  
  sensors_event_t accel, mag, gyro, temp;
  lsm9ds1.getEvent(&accel, &mag, &gyro, &temp);
  Serial.print("A ");
  Serial.print(accel.acceleration.x);  // m/s^2
  Serial.print(" | ");
  Serial.print(accel.acceleration.y);
  Serial.print(" | ");
  Serial.print(accel.acceleration.z);
  Serial.println(" -");


  Serial.print("M ");
  Serial.print(mag.magnetic.x); // gauss
  Serial.print(" | ");
  Serial.print(mag.magnetic.y);
  Serial.print(" | ");
  Serial.print(mag.magnetic.z);
  Serial.println(" -");

  Serial.print("G ");
  Serial.print(gyro.gyro.x);  // dps
  Serial.print(" | ");
  Serial.print(gyro.gyro.y);
  Serial.print(" | ");
  Serial.print(gyro.gyro.z);
  Serial.println(" -");
}



uint32_t timestamp;
void setup()
{
  Serial.begin(115200);
#ifdef DEBUG
  while (!Serial)
  {
    ;;
  }
#endif
  delay(2000); // Delay to wait for board to stabilize
  debug("Begin setup");

  pinMode(LED_BUILTIN, OUTPUT); // Setup pins
  Serial1.setRX(IBUS_RX_PIN);

  IBus.begin(Serial1, IBUSBM_NOTIMER); // iBUS connected to Serial1 RX pin
  debug("IBus started");

  //start_calibration_engine();
  debug("Calibration Engine started");


  filter.begin(FILTER_UPDATE_RATE_HZ);
  filter.setBeta(FILTER_BETA); // 1.0f is default, 0.1f is very smooth, 10.0f is very responsive
  
  debug("Filter started");
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  Wire.setSDA(20);
  Wire.setSCL(21);

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

  //debug("Attach GPS");
  //gpsPort.begin(9600);

  timestamp = millis();
  debug("Finished setup");
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

unsigned long last_update = millis();
void update_filter()
{

  if ((millis() - last_update) < (1000 / FILTER_UPDATE_RATE_HZ)) {
    return;
  }
  last_update = millis();

  float roll, pitch;
  float gx, gy, gz;

  sensors_event_t accel, gyro, mag;
  accelerometer->getEvent(&accel);
  gyroscope->getEvent(&gyro);
  magnetometer->getEvent(&mag);

  cal.calibrate(mag);
  cal.calibrate(accel);
  cal.calibrate(gyro);

  // Gyroscope needs to be converted from Rad/s to Degree/s
  // the rest are not unit-important
  gx = gyro.gyro.x * SENSORS_RADS_TO_DPS;
  gy = gyro.gyro.y * SENSORS_RADS_TO_DPS;
  gz = gyro.gyro.z * SENSORS_RADS_TO_DPS;
  filter.update(gx, gy, gz, 
                accel.acceleration.x, accel.acceleration.y, accel.acceleration.z, 
                mag.magnetic.x, mag.magnetic.y, mag.magnetic.z);


  static uint16_t print_counter = 0;
  // only print the calculated output once in a while
  if (print_counter++ <= PRINT_EVERY_N_UPDATES) {
    return;
  }
  // reset the counter
  print_counter = 0;

  // print the heading, pitch and roll
  roll = filter.getRoll();
  pitch = filter.getPitch();
  //heading = filter.getYaw();

  Serial.print("P ");
  Serial.println(pitch);
  Serial.print("R ");
  Serial.println(roll);

}

void handle_button_press(int press)
{

  // Create switch to handle
  switch (press)
  {
  case NO_PRESS:

    // No button press
    break;
  case SHORT_PRESS:

    // Short press
    break;
  case LONG_PRESS:

    // Long press
    break;
  case HELD:
    // Held
    break;
  default:
    break;
  }
}

int j = 0;
unsigned long debug_time_last_time = 0;
void loop()
{
  
  //check_gps();   // RENABLE

  handle_button_press(check_button());// HELD, NO_PRESS, SHORT_PRESS, LONG_PRESS(LONG_PRESS_MS), PRESS

  if (readIbus())
  {
    // New ibus data. Update servos and esc
    handle_ibus_update();
  }

  IBus.loop(); // Must be called once a loop


  update_filter();

#ifdef DEBUG_TIME
  if (millis() > debug_time_last_time + 1000)
  {
    debug_time_last_time = millis();
    Serial.printf("loops per ms: %i Core temperature: %2.1fC\n",(int)(j / 1000),  analogReadTemp());
    j = 0;
  }
  else
  {
    j++;
  }
#endif
}
