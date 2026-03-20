#include <WiFi.h>
#include <esp_now.h>

typedef struct {
  float temperature;
  float humidity;
} SensorData;

SensorData data;

void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));

  Serial.print("Nhận giá trị -> Nhiệt độ: ");
  Serial.print(data.temperature);
  Serial.print(" | Độ ẩm: ");
  Serial.println(data.humidity);
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  Serial.print("MAC địa chỉ: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW kết nối thất bại");
    return;
  }

  esp_now_register_recv_cb(onReceive);
}
void loop() {
}