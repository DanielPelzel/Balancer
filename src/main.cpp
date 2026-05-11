//
// Created by daniel-pelzel on 11.05.26.
//

#include <Arduino.h>
#include "config.h"
#include "mpu.h"

MPU mpu;

void setup() {
    Serial.begin(115200);
    mpu.init();
}
void loop() {
    SensorData data = mpu.readSensor();
    accAngles angles = mpu.calculateAngles(data);
    Serial.println("");
    Serial.println(angles.ax);


}
