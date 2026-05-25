#include "motor.h"

#include <Arduino.h>
#include "config.h"

Motor::Motor(int in1, int in2, int pwmKanal, int enaPin) {
    _in1 = in1;
    _in2 = in2;
    _pwmKanal = pwmKanal;
    _enaPin = enaPin;

    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    ledcSetup(_pwmKanal, PWM_FREQ, PWM_RES);
    ledcAttachPin(_enaPin, _pwmKanal);
}

void Motor::forward(int speed) {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    ledcWrite(_pwmKanal, speed);
}
void Motor::backward(int speed) {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    ledcWrite(_pwmKanal, speed);
}

void Motor::stop() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    ledcWrite(_pwmKanal, 0);
}

