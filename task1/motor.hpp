#pragma once

#include <Arduino.h>

namespace mtrn3100 {

class Motor {
public:
    Motor(uint8_t pwm_pin, uint8_t dir_pin)
        : pwm_pin(pwm_pin), dir_pin(dir_pin) {
        pinMode(pwm_pin, OUTPUT);
        pinMode(dir_pin, OUTPUT);
    }

    void setPWM(int16_t pwm) {
        bool forward = pwm >= 0;
        pwm = abs(pwm);
        if (pwm > 255) pwm = 255;

        digitalWrite(dir_pin, forward ? HIGH : LOW);
        analogWrite(pwm_pin, pwm);
    }

private:
    const uint8_t pwm_pin;
    const uint8_t dir_pin;
};

}  // namespace mtrn3100
