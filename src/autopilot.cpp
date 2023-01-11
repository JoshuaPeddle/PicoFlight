#include "autopilot.h"


bool auto_leveling = false;

int roll_offset = 0;



unsigned long last_filter_update = millis();
void update_filter()
{

  if ((millis() - last_filter_update) < (1000 / FILTER_UPDATE_RATE_HZ)) {
    return;
  }
  last_filter_update = millis();

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

  auto_level();
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




void auto_level()
{
  if (!auto_leveling)
  {
    return;
  }
  float roll_zero = 0;
  float roll, pitch;
  float delta_roll;
  float roll_servo;
  int servo_zero_point = 1500;
  int servo_max = 2000;
  int servo_min = 1000;
  int servo_range = servo_max - servo_min;
  int servo_range_half = servo_range / 2;

  roll = filter.getRoll();
  pitch = filter.getPitch();

  delta_roll = roll - roll_zero;

  // print the delta roll
  //Serial.print("DR ");
  //Serial.println(delta_roll);

  roll_offset = -delta_roll * AUTO_LEVEL_ALPHA;

  // Apply the roll offset
  handle_ibus_update();

}
