https://github.com/earlephilhower/arduino-pico
https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf
https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf
https://github.com/bmellink/IBusBM
https://i0.wp.com/peppe8o.com/wp-content/uploads/2021/05/raspberry-pi-pico-pinout-featured-image.jpg?w=1200&ssl=1


Configure pins in pins.h

Implemented features:
ESC support (connections to 1 ESC)
Servo support (connections to Elevator, Aileron(Single and Dual), Rudder, Thrust)
IBUS support (connections to FlySky RC Receivers)
9DOF IMU Support (only lsm6ds1 supported, data is not used)
AHRS support (mahoney, madgwick and NXP fusion solutions)


TODO (In rough order):
Flight stabilization using PID system with AHRS
GPS support






Supported targets:
Raspberry Pi Pico (using earlephilhower/arduino-pico library)

