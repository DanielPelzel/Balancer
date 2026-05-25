#include "mpu.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "config.h"

MPU::MPU(){
     angle = 0.0f;
     offset = 0.0f;
     lastTime = 0.0f;
}

bool MPU::init() {

     Serial.println("Serching for MPU");

     //Connecting pins
     Wire.begin(SDA_PIN, SCL_PIN);

     //test ifg connection is possible

     if (!mpu.begin()) {
          Serial.println("Could not find MPU device!");
          return false;
     }else {
          Serial.println("MPU found!");


          mpu.setAccelerometerRange(MPU_accel_Range);
          mpu.setGyroRange(MPU_gyro_Range);
          mpu.setFilterBandwidth(MPU_filter_bandwidth);
          return true;
     }
}

SensorData MPU::readSensor(){
     sensors_event_t a,g,temp;
     mpu.getEvent(&a, &g, &temp);

     //get data
     SensorData data;
     data.ax = a.acceleration.x;
     data.ay = a.acceleration.y;
     data.az = a.acceleration.z;
     data.gx = g.gyro.x;
     data.gy = g.gyro.y;
     data.gz = g.gyro.z;

     return data;
}

accAngles MPU::calculateAngles(SensorData data) {

     //acc angles
     angles.ax = atan2(data.ay, data.az) *180 / PI;
     angles.ay = atan2(data.ax, data.az) *180 / PI;
     angles.az = atan2(data.ax, data.ay) *180 / PI;

     return angles;
}

filteredAngles MPU::filter(SensorData data) {
     unsigned long now = millis();
     float dt = (now-lastTime) / 1000.0f;
     lastTime = now;

     filtered.ax = 0.98f * (filtered.ax + data.gx * dt) + angles.ax *0.02f;
     filtered.ay = 0.98f * (filtered.ay + data.gy * dt) + angles.ay *0.02f;
     filtered.az = 0.98f * (filtered.az + data.gz * dt) + angles.az *0.02f;

     return filtered;

}

void MPU::calibrate() {
     float sum = 0.0f;
     for (int i = 0; i < 100; i++) {
          SensorData data = readSensor();
          calculateAngles(data);
          sum += angles.drehachse;
     }
     offset = sum /100.0f;
}

float MPU::getError(){
    SensorData data = readSensor();
     calculateAngles(data);
     filteredAngles f =filter(data);
     return f.drehachse - offset;
};
