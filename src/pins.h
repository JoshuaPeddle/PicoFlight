// Servo setup
#define ELEVATOR_PIN 2
#define DUAL_AILERON
#ifdef DUAL_AILERON
#define LEFT_AILERON_PIN 3
#define RIGHT_AILERON_PIN 4
#else
#define AILERON_PIN 3
#endif
#define RUDDER_PIN 5

// Esc setup
#define THROTTLE_PIN 6

// IBUS receiver setup
#define IBUS_RX_PIN 1