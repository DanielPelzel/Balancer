#include "balancer.h"
#include "config.h"
#include "motor.h"
#include <Arduino.h>
#include "pid.h"
#include "mpu.h"
Balancer::Balancer()
    :_motorLinks(In1, In2, PWM_CH_A1, PWM_CH_A2)
    ,_motorRechts(In3, In4, PWM_CH_B1, PWM_CH_B2)
    , _mpu()
    , _pid(KP, KI, KD)
{ }

void Balancer::init() {
    pinMode(SLEEP_PIN, OUTPUT);
    digitalWrite(SLEEP_PIN, HIGH);
    _mpu.init();
    _mpu.calibrate();
}

void Balancer::forward(int speed) {
    _motorRechts.forward(speed);
    _motorLinks.forward(speed);
}

void Balancer::backward(int speed) {
    _motorRechts.backward(speed);
    _motorLinks.backward(speed);
}

void Balancer::stop() {
    _motorRechts.stop();
    _motorLinks.stop();
}

float Balancer::update() {
    float error = _mpu.getError();
    float output = _pid.output(error);
    output = constrain(output, -255, 255);

    if (output > 0) output = map(output, 0, 255, TOTPUNKT, 255);
    if (output < 0) output = map(output, -255, 0, -255, -TOTPUNKT);

    if (output > 0) {
        forward(int(output));
    }else if (output < 0) {
        backward(int(-output));
    }else{
        stop();
    }
    return output;
}

void Balancer::setPID(float kp, float ki, float kd) {
    _pid.setGains(kp, ki, kd);
}