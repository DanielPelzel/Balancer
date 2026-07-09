#pragma once
#include <Arduino.h>

class Motor {
private:
    int _in1, _in2;
    int _pwmCh1, _pwmCh2;

public:
    Motor(int in1, int in2, int pwmCh1, int pwmCh2);
    void forward(int speed);
    void backward(int speed);
    void stop();
};
