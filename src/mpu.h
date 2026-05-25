#pragma once
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


struct SensorData {
    float ax, ay, az;
    float gx, gy, gz;
};

struct accAngles {
    float ax, ay, az;
};

struct filteredAngles {
    float ax, ay, az;
};


class MPU {
private:
    Adafruit_MPU6050 mpu;
    accAngles angles;
    filteredAngles filtered = {0.0f, 0.0f, 0.0f};
    float angle;
    float offset;
    unsigned long lastTime;




public:
    MPU();
    bool init();
    void calibrate();
    SensorData readSensor();
    accAngles calculateAngles(SensorData angles);
    filteredAngles filter(SensorData data);
    float getError();

};