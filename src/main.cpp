//
// Created by daniel-pelzel on 11.05.26.
//

#include <Arduino.h>
#include "config.h"
#include "mpu.h"
#include "communiation.h"

MPU mpu;
Communication com;

void setup() {
    Serial.begin(115200);
    mpu.init();
    mpu.calibrate();
}
void loop() {
   float angle = mpu.getAngle();
    com.sendData(angle);
    delay(10);



}
