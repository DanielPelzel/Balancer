#include "PID.h"
#include "config.h"
#include <Arduino.h>

PID::PID(float kp, float ki, float kd) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _integral = 0;
    _lastError = 0;
    _lastTime = millis();
}

float PID::output(float error) {

    //time
    unsigned long now = millis();
    float dt = (now - _lastTime) / 1000.0f;

    _integral += error * dt;


    _rate = (error - _lastError) / dt;


    //pid berechnen
    float p = _kp * error;
    float i = _ki * _integral;
    float d = kd * _rate;

    //Werte aktuallisierne
    _lastError = error;
    _lastTime = now;

    return p + i + d;

}