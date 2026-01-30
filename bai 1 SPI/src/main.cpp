#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SPI.h>

#define BME_SCK 25
#define BME_MISO 32
#define BME_MOSI 26
#define BME_CS 33

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

unsigned long delayTime;

void printValues();

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));
  
  bool status;
  
  status = bme.begin();  
  if (!status) {
    Serial.println("Khong the tim cam bien BME280, kiem tra day!");
    while (1);
  }
  
  Serial.println("-- Default Test --");
  delayTime = 1000;
  Serial.println();
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  
  Serial.println();
}
void loop() { 
  printValues();
  delay(delayTime);
}