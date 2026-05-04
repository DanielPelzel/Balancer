#include "Balancer.h"
#include "config.h"
#include "motor.h"
#include <Arduino.h>

Balancer::Balancer()
    :_motorLinks(In1, In2, PWM_CH_A, ENA)
    ,_motorRechts(In3, In4, PWM_CH_B,ENB)
{}

void Balancer::forward(int speed) {
    _motorLinks.forward(speed);
    _motorRechts.forward(speed);
}

void Balancer::backward(int speed) {
    _motorLinks.backward(speed);
    _motorRechts.backward(speed);
}

void Balancer::stop() {
    _motorLinks.stop();
    _motorRechts.stop();
}