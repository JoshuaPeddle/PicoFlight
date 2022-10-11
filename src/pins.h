// Servo setup


#define DUAL_AILERON

#ifdef DUAL_AILERON

#define LEFT_AILERON_PIN 3
#define LEFT_AILERON_IBUS_CHANNEL 4

#define RIGHT_AILERON_PIN 4
#define RIGHT_AILERON_IBUS_CHANNEL 4

#else

#define AILERON_PIN 3
#define AILERON_IBUS_CHANNEL 1

#endif


#define RUDDER_PIN 5
#define RUDDER_IBUS_CHANNEL 1

#define ELEVATOR_PIN 2
#define ELEVATOR_IBUS_CHANNEL 2

// Esc setup
#define THROTTLE_PIN 7
#define THROTTLE_IBUS_CHANNEL 3

// IBUS receiver setup
#define IBUS_RX_PIN 1