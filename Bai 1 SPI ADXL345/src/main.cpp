#include <Arduino.h>
#include <SPI.h>
#include <SparkFun_ADXL345.h>

#define CS_PIN 5

ADXL345 accel(CS_PIN);

void setup() {
  Serial.begin(9600);
  delay(500);
  SPI.begin();
  accel.powerOn();          
  accel.setRangeSetting(2); 
  accel.setSpiBit(0);       
  Serial.println("ADXL345 - Bắt đầu đọc");
}

void loop() {
  int x, y, z;
  accel.readAccel(&x, &y, &z);

  Serial.print("X: "); Serial.print(x);
  Serial.print(" Y: "); Serial.print(y);
  Serial.print(" Z: "); Serial.println(z);

  delay(500);
}