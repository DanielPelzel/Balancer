
#pragma once
#include "balancer.h"

class Communication {

    public:
    void sendData(float angle, float motorOutput);
    void receiveData(Balancer& balancer);

};