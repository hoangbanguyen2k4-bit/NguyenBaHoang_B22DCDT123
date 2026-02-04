#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 4 
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    delay(2000);
    Serial.begin(9600);
    Serial.println(F("DHT11 - Bắt đầu đọc"));
    dht.begin();    
}

void loop()
{
    delay(2000);
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Không nhận được dữ liệu từ DHT11!"));
        return;
    }
    
    Serial.print(F("Độ ẩm: "));
    Serial.print(h);
    Serial.print(F("% | Nhiệt độ: "));
    Serial.print(t);
    Serial.println(F("°C"));
}