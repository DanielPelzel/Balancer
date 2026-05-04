#include <Arduino.h>

#include "balancer.h"
#include "config.h"
#include "motor.h"
#include "mpu.h"


Balancer balancer;

void setup() {
    Serial.begin(115200);
    balancer.init();
}

void loop() {
    balancer.update();
    //Test axis

}
