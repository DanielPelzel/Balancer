#pragma once
#include "motor.h"
#include "config.h"

class Balancer {
private:
    Motor _motorLinks;
    Motor _motorRechts;
public:
    Balancer();
    void forward(int speed);
    void backward(int speed);
    void stop();
};