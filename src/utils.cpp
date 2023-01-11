#include "utils.h"
#define DEBUG
#include "lsm9ds1.h"

void debug(const String str)
{
#ifdef DEBUG
  Serial.println(str);
#endif
}

void debug(const char *str)
{
#ifdef DEBUG
  Serial.println(str);
#endif
}

void debug(int str)
{
#ifdef DEBUG
  Serial.println(str);
#endif
}


void blink(int del)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(del);
  digitalWrite(LED_BUILTIN, LOW);
  delay(del);
}

void say_hello()
{
  debug("Hello World!");
}


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

