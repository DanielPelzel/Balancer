#include "balancer.h"
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
    , _pid(KP, KI, KD)
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
    float error = angle - _targetAngle;
    float output = _pid.output(error);
    output = constrain(output, -255, 255);

    if (output > 0 && output < 80) output = 80;
    if (output < 0 && output > -80) output = 80;

    if (output > 0) {
        forward(int(output));
    }else if (output < 0) {
        backward(int(-output));
    }else{
        stop();
    }
}

bool Balancer::init() {
    _mpu.init();
    _mpu.calibrate();
    return true;
}

float Balancer::getAngle() {
    return _mpu.angle()*180/PI;
}

void Balancer::printData() {
    _mpu.printData();
}
