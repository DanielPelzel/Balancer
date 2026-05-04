#include "Balancer.h"
#include "config.h"
#include "motor.h"
#include <Arduino.h>
#include "pid.h"
#include "mpu.h"

Balancer::Balancer()
    :_motorLinks(In1, In2, PWM_CH_A, ENA)
    ,_motorRechts(In3, In4, PWM_CH_B,ENB)
    ,_targetAngle(0.0f)
    , _mpu()
    , _pid(kp, ki, kd)
{ }


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

void Balancer::update() {
    float angle = _mpu.angle();
    float errpop = angle - _targetAngle;


}