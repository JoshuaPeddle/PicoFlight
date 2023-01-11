#include "autopilot.h"


bool auto_leveling = false;

int roll_offset = 0;


struct filterData {
  float roll;
  float pitch;
  float yaw;
};
// A stack class to hold the filter data. Number held is defined by the
// AUTO_LEVELING_SMOOTHING
class FilterStack {
  public:
    FilterStack() {
      _index = 0;
    }
    void push(filterData data) {
      _data[_index] = data;
      _index++;
      if (_index >= AUTO_LEVELING_SMOOTHING) {
        _index = 0;
      }
    }
    filterData getAverage() {
      filterData average;
      average.roll = 0;
      average.pitch = 0;
      average.yaw = 0;
      for (int i = 0; i < AUTO_LEVELING_SMOOTHING; i++) {
        average.roll += _data[i].roll;
        average.pitch += _data[i].pitch;
        average.yaw += _data[i].yaw;
      }
      average.roll /= AUTO_LEVELING_SMOOTHING;
      average.pitch /= AUTO_LEVELING_SMOOTHING;
      average.yaw /= AUTO_LEVELING_SMOOTHING;
      return average;
    }
  private:
    filterData _data[AUTO_LEVELING_SMOOTHING];
    int _index;
};

FilterStack filterStack;
unsigned long last_filter_update = millis();
void update_filter()
{

  if ((millis() - last_filter_update) < (1000 / FILTER_UPDATE_RATE_HZ)) {
    return;
  }
  last_filter_update = millis();

  float roll, pitch, heading;
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

  // print the heading, pitch and roll
  roll = filter.getRoll();
  pitch = filter.getPitch();
  heading = filter.getYaw();

  // Update the filter stack
  filterData data;
  data.roll = roll;
  data.pitch = pitch;
  data.yaw = heading;
  filterStack.push(data);


  auto_level();
  static uint16_t print_counter = 0;
  // only print the calculated output once in a while
  if (print_counter++ <= PRINT_EVERY_N_UPDATES) {
    return;
  }
  // reset the counter
  print_counter = 0;
  filterData filtered_data = filterStack.getAverage();
  Serial.print("P ");
  Serial.println(filtered_data.pitch);
  Serial.print("R ");
  Serial.println(filtered_data.roll);
  Serial.print("Y ");
  Serial.println(filtered_data.yaw);



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

  roll = filterStack.getAverage().roll;
  pitch = filterStack.getAverage().pitch;

  delta_roll = roll - roll_zero;

  // print the delta roll
  //Serial.print("DR ");
  //Serial.println(delta_roll);

  roll_offset = -delta_roll * AUTO_LEVEL_ALPHA;


}
