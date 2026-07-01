#include <Arduino.h>
#include "config.h"
#include "balancer.h"
#include "communiation.h"

Balancer balancer;
Communication com;

void setup() {
    Serial.begin(115200);
    balancer.init();
}

void loop() {
    float output = balancer.update();

    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 20) {
        com.sendData(balancer.getAngle(), output);
        lastPrint = millis();
    }
    com.receiveData(balancer);
    delay(5);
}