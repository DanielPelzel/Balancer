#pragma once

#include "motor.h"
#include "config.h"
#include "mpu.h"
#include "pid.h"

class Balancer {
private:
    Motor _motorLinks;
    Motor _motorRechts;
    MPU _mpu;
    Pid _pid;

public:
    Balancer();
    void init();
    void forward(int speed);
    void backward(int speed);
    void stop();
    float update();
    void setPID(float kp, float ki, float kd);
    float getAngle() { return _mpu.getError(); }
};