#include <Arduino.h>

#include "balancer.h"
#include "config.h"
#include "motor.h"


Balancer balancer;

void setup() {
    Serial.begin(115200);
}

void loop() {
    balancer.forward(200);
    delay(1000);
    balancer.stop();
    delay(1000);
    balancer.backward(200);
    delay(1000);

}
