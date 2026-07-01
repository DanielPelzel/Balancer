#include "communiation.h"
#include "mpu.h"
#include "pid.h"



void Communication::sendData(float angle, float motorOutput) {
    Serial.print(angle);
    Serial.print(",");
    Serial.println(motorOutput);

}

void Communication::receiveData(Balancer& balancer) {
    if (Serial.available()) {
        String msg = Serial.readStringUntil('\n');
        float p, i, d;
        sscanf(msg.c_str(), "p:%f, i:%f, d:%f", &p, &i, &d);
        balancer.setPID(p,i,d);
    }
}