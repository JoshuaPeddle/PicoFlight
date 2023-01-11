#ifndef PINS_H
#define PINS_H

#define DUAL_AILERON


// Servo pin setup
#ifdef DUAL_AILERON
    #define LEFT_AILERON_PIN 8
    #define RIGHT_AILERON_PIN 4
#else
    #define AILERON_PIN 3
#endif

#define RUDDER_PIN 2

#define ELEVATOR_PIN 1

#define THROTTLE_PIN 0

// Ibus aileron, elevator, rudder and throttle channel setup
#ifdef DUAL_AILERON
    #define LEFT_AILERON_IBUS_CHANNEL 4
    #define RIGHT_AILERON_IBUS_CHANNEL 4
#else
    #define AILERON_IBUS_CHANNEL 1
#endif

#define RUDDER_IBUS_CHANNEL 1

#define ELEVATOR_IBUS_CHANNEL 2

#define THROTTLE_IBUS_CHANNEL 3

// Ibus aux channel setup 
#define VRA_IBUS_CHANNEL 5

#define VRB_IBUS_CHANNEL 6

#define SWA_IBUS_CHANNEL 7

#define SWB_IBUS_CHANNEL 8

#define SWC_IBUS_CHANNEL 9

#define SWD_IBUS_CHANNEL 10

// IBUS UART receiver setup
#define IBUS_RX_PIN 13

// LSM9DS1 i2c pins
#define LSM9DS1_SDA 20
#define LSM9DS1_SCL 21

#endif