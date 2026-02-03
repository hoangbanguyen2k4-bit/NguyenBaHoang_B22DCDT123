#include <Wire.h>
#include <MAX30105.h>
#include "heartRate.h"

MAX30105 particleSensor;
long lastBeat = 0;
float currentBPM = 0;
unsigned long lastDisplay = 0;
bool fingerDetected = false;
void setup() {
    Serial.begin(9600);
    
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("Không nhận được dữ liệu từ MAX30102!");
        while(1);
    }
    
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x0A);
    
    Serial.println("MAX30102 - Cảm biến nhịp tim");
}

void loop() {
    long irValue = particleSensor.getIR();
    
    if (irValue > 50000 && checkForBeat(irValue)) {
        float bpm = 60 / ((millis() - lastBeat) / 1000.0);
        lastBeat = millis();
        
        if (bpm > 40 && bpm < 180) {
            Serial.print("BPM: ");
            Serial.println(bpm, 1);
        }
    }
    delay(10);
}