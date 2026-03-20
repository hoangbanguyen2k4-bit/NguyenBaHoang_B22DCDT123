#include <WiFi.h>
#include <esp_now.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

uint8_t receiverMAC[] = {0x68, 0xFE, 0x71, 0xFA, 0x6E, 0xD0};

typedef struct {
  float temperature;
  float humidity;
} SensorData;

SensorData data;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  dht.begin();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW kết nối thất bại");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);
}

void loop() {
  data.temperature = dht.readTemperature();
  data.humidity = dht.readHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Đọc cảm biến thất bại!");
    return;
  }

  esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));

  Serial.print("Gửi giá trị -> Nhiệt độ: ");
  Serial.print(data.temperature);
  Serial.print(" | Độ ẩm: ");
  Serial.println(data.humidity);

  delay(2000);
}