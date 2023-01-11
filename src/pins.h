#ifndef PINS_H
#define PINS_H


#define DUAL_AILERON

#ifdef DUAL_AILERON

#define LEFT_AILERON_PIN 8
#define LEFT_AILERON_IBUS_CHANNEL 4

#define RIGHT_AILERON_PIN 4
#define RIGHT_AILERON_IBUS_CHANNEL 4

#else

#define AILERON_PIN 3
#define AILERON_IBUS_CHANNEL 1

#endif


#define RUDDER_PIN 2
#define RUDDER_IBUS_CHANNEL 1

#define ELEVATOR_PIN 1
#define ELEVATOR_IBUS_CHANNEL 2

// Esc setup
#define THROTTLE_PIN 0
#define THROTTLE_IBUS_CHANNEL 3

// IBUS receiver setup
#define IBUS_RX_PIN 13

#define LSM9DS1_SDA 20
#define LSM9DS1_SCL 21

#endif