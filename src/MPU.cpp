#include <Adafruit_MPU6050.h>
#include "mpu.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "config.h"

MPU::MPU() {
    _angle = 0;
    _offset = 0;
    _lastTime = 0;
}

bool MPU::init() {
    Wire.begin(SDA,SCL);

    if (!_mpu.begin()) {
        Serial.println("MPU6050 not found");
        return false;
    }else {

        _mpu.setAccelerometerRange(MPU_accel_Range);
        _mpu.setGyroRange(MPU_gyro_Range);
        _mpu.setFilterBandwidth(MPU_filter_bandwidth);


        Serial.println("MPU6050 found");
        return true;
    }

}

void MPU::calibrate() {
    float sum = 0;
    for (int i = 0; i < 100; i++) {
        sum += angle();
        delay(10);
    }
    _offset = sum / 100.0f;
}

float MPU::angle() {

    unsigned long now = millis();
    float dt = (now - _lastTime) / 1000.0f;

    sensors_event_t a, g ,temp;
    _mpu.getEvent(&a, &g, &temp);

    float accel_angle =  atan2(a.acceleration.y, a.acceleration.z) * 180 / PI;

    float gyroRate = g.gyro.x *180/PI ;
    float gyro_angle = _angle + gyroRate * dt;

    //TODO filter methode aufrufen
    _angle = filter(_angle, accel_angle);

    _lastTime = now;

    return _angle - _offset;
}

float MPU::filter(float accelAngle, float gyrongle) {
    float output = accelAngle * 0.98 + gyrongle * 0.02;
    return output;
}


float MPU::offset() {
    float sum = 0;

    for (int i = 0; i < 100; i++) {
        angle();
        sum += _angle;
    }
    _offset = sum / 100;
    return _offset;
}