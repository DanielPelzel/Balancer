#include <Arduino.h>
#include "config.h"



void setup() {
    Serial.begin(115200);

    ledcSetup(0, 1000, 8); //Kanal 0 mit 1000er Frequenz und 8 bit
    ledcSetup(1, 1000, 8);

    ledcAttachPin(ENB, 0); //ENB zum PWM Kanal 0 verbinden
    ledcAttachPin(ENA, 1); //ENA zum PWM Kanal 1 verbinden

    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);

    pinMode(Enc_A_R, INPUT);
    pinMode(Enc_B_R, INPUT);
    pinMode(Enc_A_L, INPUT);
    pinMode(Enc_B_L, INPUT);
}



//Gewschwindigkeit wird in 0-255 übergeben
void forward(int speed) {


    digitalWrite(In4, HIGH);
    digitalWrite(In3, LOW);
    ledcWrite(0, speed);

    digitalWrite(In2, HIGH);
    digitalWrite(In1, LOW);
    ledcWrite(1, speed);

}

void stop() {
    digitalWrite(In4, LOW);
    digitalWrite(In3, LOW);
    ledcWrite(0, 0);

    digitalWrite(In2, LOW);
    digitalWrite(In1, LOW);
    ledcWrite(1, 0);
}

void backward(int speed) {

    digitalWrite(In4, LOW);
    digitalWrite(In3, HIGH);
    ledcWrite(0, speed);

    digitalWrite(In2, LOW);
    digitalWrite(In1, HIGH);
    ledcWrite(1, speed);

}


void loop() {

}
