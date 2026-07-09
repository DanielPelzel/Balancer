#include <Arduino.h>

#define IN1 32
#define IN2 33
#define ENA 13
#define PWM_CH 0

void setup() {
    Serial.begin(115200);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    ledcSetup(PWM_CH, 5000, 8);
    ledcAttachPin(ENA, PWM_CH);
    ledcWrite(PWM_CH, 200);
    
    Serial.println("Vorwärts");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(2000);
    
    Serial.println("Stop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    delay(1000);
    
    Serial.println("Rückwärts");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(2000);
}

void loop() {}