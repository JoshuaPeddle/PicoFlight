

# Autopilot


## AutoLeveling
AutoLeveling is a PID controller that tries to keep the craft level. It uses onboard sensors to determine the current angle of the craft and tries to keep it at 0°.

The sensor data is provided by a lsm9ds1 9 dof sensor. The sensor is connected to the pico via i2c. The data is filtered using Mahony or Madgwick filter. This filtered data is then used by the PID controller to keep the craft level.

Two important defines are 'AUTO_LEVEL_ALPHA' and "AUTO_LEVEL_SMOOTHING'. Relationship between the delta pitch as determined by the filter and the roll offset. The second one decides how many filtered data results are averaged together to get a smoother result.

## Button
Button manages the button on the pico, if using a microcontroller with a button, this can be used to provide a button interface. Events such as LONG_PRESS and SHORT_PRESS can be used to implement custom functionality.
### Implementated Events
SHORT_PRESS | LONG_PRESS | HELD | PRESS 

## ESC


## IBUS


## LSM9DS1


## PINS


## SERVO


## UTILS
