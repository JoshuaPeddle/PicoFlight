#include <servos.h>


ESC esc;

Servo elevator;
#ifdef DUAL_AILERON
Servo left_aileron;
Servo right_aileron;
#else
Servo aileron;
#endif
Servo rudder;
