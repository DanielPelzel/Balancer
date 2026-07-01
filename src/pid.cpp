#include "pid.h"
#include <Arduino.h>

Pid::Pid(float kp, float ki, float kd) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _lastTime = millis();
    _lastError = 0.0f;
    _integral = 0.0f;
}

float Pid::output(float error) {
    unsigned long now = millis();
    float dt = (now - _lastTime) / 1000.0f;

    _integral += error * dt;

    float rate = (error - _lastError) / dt;

    float p = _kp * error;
    float i = _ki * _integral;
    float d = _kd * rate;

    _lastError = error;
    _lastTime = now;

    return p + i + d;
}

void Pid::setGains(float kp, float ki, float kd) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
}
