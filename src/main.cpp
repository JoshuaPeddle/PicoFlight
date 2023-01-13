#include "main.h"


NMEAGPS gps; // This parses the GPS characters
gps_fix fix; // This holds on to the latest values



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

  roll_offset = 0;
  
  debug("Filter started");
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  Wire.setSDA(LSM9DS1_SDA);
  Wire.setSCL(LSM9DS1_SCL);

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

  debug("Finished setup");
}

int loops_since_ibus_loop = 0;

void loop()
{
  static int j = 0;
  static unsigned long debug_time_last_time = 0;
  //check_gps();   // RENABLE

  // Check the button for the events defined in button.h
  handle_button_press(check_button());

  if (loops_since_ibus_loop++ > IBUS_LOOPS_TO_SKIP) //TODO: Smart calculate this according this to current loop time
  {
    loops_since_ibus_loop = 0;
    IBus.loop();
    // Check if new data was received on the ibus RX
    if (readIbus()){ /* Handle new ibus data. */}
  }


  // Update the filter using the onbaord sensor data
  update_filter();

  // Update the servos using the filter data
  write_servos();
  
#ifdef DEBUG_TIME
  if (millis() > debug_time_last_time + 3000)
  {
    debug_time_last_time = millis();
    Serial.printf("loops per ms: %i Core temperature: %2.1fC\n",(int)(j / 3000), (double) analogReadTemp());
    j = 0;
  }
  else
  {
    j++;
  }
#endif
}



void check_gps()
{
  static unsigned long last_gps_check = 0; // When the last actual check of the buttons physical states was
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

