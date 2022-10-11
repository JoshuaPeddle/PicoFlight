#include "esc.h"


Servo motor;

ESC::ESC(int pin)
{
    motor.attach(pin);
}

void ESC::set_esc_pulse(short pulse)
{
    if (pulse < MINIMUM_INPUT_PULSE || pulse > MAXIMUM_INPUT_PULSE)
        Serial.println("[ERROR] Invalid value for pulse in set_esc_pulse");
        return ;
    motor.writeMicroseconds(improved_map(pulse));
}

void ESC::set_esc_percent(float percent)
{
    if (percent < 0 || percent > 100)
        return ;
    // map the precentage to pulse
    short input_pulse = improved_map2(percent, 0, 100, MINIMUM_INPUT_PULSE, MAXIMUM_INPUT_PULSE);
    set_esc_pulse(input_pulse);
}


// Similar to map but will have increased accuracy that provides a more
// symmetrical api (call it and use result to reverse will provide the original value)
int improved_map2(int value, int minIn, int maxIn, int minOut, int maxOut) {
    const int rangeIn = maxIn - minIn;
    const int rangeOut = maxOut - minOut;
    const int deltaIn = value - minIn;
    // fixed point math constants to improve accuracy of divide and rounding
    constexpr int fixedHalfDecimal = 1;
    constexpr int fixedDecimal = fixedHalfDecimal * 2;

    return ((deltaIn * rangeOut * fixedDecimal) / (rangeIn) + fixedHalfDecimal) / fixedDecimal + minOut;
}
int improved_map(short value) {
    const int rangeIn = MAXIMUM_INPUT_PULSE - MINIMUM_INPUT_PULSE;
    const int rangeOut = MAXIMUM_SAFE_ESC_PULSE - MINIMUM_SAFE_ESC_PULSE;
    const int deltaIn = value - MINIMUM_INPUT_PULSE;
    // fixed point math constants to improve accuracy of divide and rounding
    constexpr int fixedHalfDecimal = 1;
    constexpr int fixedDecimal = fixedHalfDecimal * 2;

    return ((deltaIn * rangeOut * fixedDecimal) / (rangeIn) + fixedHalfDecimal) / fixedDecimal + MINIMUM_SAFE_ESC_PULSE;
}
