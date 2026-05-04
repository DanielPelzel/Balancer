#pragma once
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


class MPU {
private:
    Adafruit_MPU6050 _mpu;
    float _angle;
    float _offset;
    float _lastTime;

public:
MPU();
bool init();
float angle();
float offset();
float filter(float accelAngle, float gyroAngle);
void calibrate();


};