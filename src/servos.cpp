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

unsigned long last_servo_update = millis();
void write_servos()
{
    unsigned long now = millis();
    if ((now - last_servo_update) < (1000 / SERVO_UPDATE_RATE_HZ))
    {
        return;
    }
    last_servo_update = now;

    // debug("IBUS updated");
    elevator.writeMicroseconds(ibus_data.get_channel_value(ELEVATOR_IBUS_CHANNEL));
#ifdef DUAL_AILERON
    left_aileron.writeMicroseconds(ibus_data.get_channel_value(LEFT_AILERON_IBUS_CHANNEL) + roll_offset);
    right_aileron.writeMicroseconds(ibus_data.get_channel_value(RIGHT_AILERON_IBUS_CHANNEL) - roll_offset);
    // Serial.println(ibus_data.get_channel_value(RIGHT_AILERON_IBUS_CHANNEL) + roll_offset);
#else
    aileron.writeMicroseconds(ibus_data.get_channel_value(AILERON_IBUS_CHANNEL));
#endif
    rudder.writeMicroseconds(ibus_data.get_channel_value(RUDDER_IBUS_CHANNEL));

    esc.set_esc_pulse(ibus_data.get_channel_value(THROTTLE_IBUS_CHANNEL));
}
