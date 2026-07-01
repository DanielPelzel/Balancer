//
// Created by daniel-pelzel on 11.05.26.
//

#include <Arduino.h>
#include "config.h"
#include "mpu.h"
#include "communiation.h"
#include "balancer.h"

MPU mpu;
Communication com;
Balancer balancer;

void setup() {
    Serial.begin(115200);
    balancer.init();
    mpu.init();
    mpu.calibrate();
}
void loop() {
    float output = balancer.update();
    float angle = mpu.getError();
    com.sendData(angle, output);
    com.receiveData(balancer);
    delay(10);

}
