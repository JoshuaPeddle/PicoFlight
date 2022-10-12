# PicoFlight - A lightweight flight computer for the Raspberry Pi Pico

## Implemented features:
- ESC support (connections to 1 ESC motor combo)
- Servo support (connections to Elevator, Aileron(Single and Dual), Rudder, Thrust)
- IBUS support (connections to FlySky RC Receivers)
- 9DOF IMU Support (only lsm6ds1 supported, data is not used)
- AHRS support (mahoney, madgwick and NXP fusion solutions)

## TODO (In rough order):
- Flight stabilization using PID system with AHRS
- GPS support


## Supported targets:
- Raspberry Pi Pico (using earlephilhower/arduino-pico library)

## Supporting resources:
- [Arduino-Pico](https://github.com/earlephilhower/arduino-pico)
- [Raspberry Pi rp2040 datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
- [Raspberry Pi Pico datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf)
- [Bmellink ibus library](https://github.com/bmellink/IBusBM)
- [Raspberry Pi Pico pinout](https://i0.wp.com/peppe8o.com/wp-content/uploads/2021/05/raspberry-pi-pico-pinout-featured-image.jpg?w=1200&ssl=1)

## Instructions:
- Configure pins in pins.h