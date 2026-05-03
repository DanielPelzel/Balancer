#ifndef MOTOR_H
#define MOTOR_H
#include <cstdint>

class Motor {
private:

public:
    Motor();
    void forward(uint8_t speed);
    void backward(uint8_t speed);
    void stop();

};
