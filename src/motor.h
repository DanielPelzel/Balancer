#pragma once
#include <Arduino.h>

class Motor {
private:
    int _in1, _in2;
    int _pwmKanal;
    int _enaPin;

public:
    Motor(int in1, int in2, int pwmKanal, int enaPin);
    void forward(int speed);
    void backward(int speed);
    void stop();
};