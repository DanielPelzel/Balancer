#pragma once
#include "motor.h"
#include "config.h"
#include "mpu.h"
#include "pid.h"

class Balancer {
private:
    Motor _motorLinks;
    Motor _motorRechts;
    float _targetAngle;
    MPU _mpu;
    PID _pid;
    float _angle;
public:
    Balancer();
    void forward(int speed);
    void backward(int speed);
    void stop();
    void update();
    bool init();
    float getAngle();
    void printData();

};