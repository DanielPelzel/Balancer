#include <Arduino.h>

#include "balancer.h"
#include "config.h"
#include "motor.h"
#include "mpu.h"
#include "pid.h"
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>


Balancer balancer;



void setup() {
    Serial.begin(115200);
    balancer.init();
}

void loop() {
    float angle = balancer.getAngle();
    Serial.println(angle);
    delay(100);

}
