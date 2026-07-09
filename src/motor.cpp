#include "motor.h"

#include <Arduino.h>
#include "config.h"

Motor::Motor(int in1, int in2, int pwmCh1, int pwmCh2) {
    _in1 = in1;
    _in2 = in2;
    _pwmCh1 = pwmCh1;
    _pwmCh2 = pwmCh2;

    ledcSetup(_pwmCh1, PWM_FREQ, PWM_RES);
    ledcSetup(_pwmCh2, PWM_FREQ, PWM_RES);
    ledcAttachPin(_in1, _pwmCh1);
    ledcAttachPin(_in2, _pwmCh2);
}

void Motor::forward(int speed) {
    ledcWrite(_pwmCh1, speed);
    ledcWrite(_pwmCh2, 0);
}

void Motor::backward(int speed) {
    ledcWrite(_pwmCh1, 0);
    ledcWrite(_pwmCh2, speed);
}

void Motor::stop() {
    ledcWrite(_pwmCh1, 0);
    ledcWrite(_pwmCh2, 0);
}
