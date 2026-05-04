#pragma once

class PID{
private:
    float _kp; //propotrional
    float _ki; //integral
    float _kd; //differential
    float _integral;
    float _lastError;
    unsigned long _lastTime;

public:
    PID(float kp, float ki, float kd);
    float output(float error);
    void reset();
};