#pragma once

class Pid {
private:
    float _kp;
    float _ki;
    float _kd;
    float _lastTime;
    float _lastError;
    float _integral;
public:
    Pid(float kp, float ki, float kd);
    float output(float error);
    void setGains(float kp, float ki, float kd);

};