#include<ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  int n = WiFi.scanNetworks();
  Serial.println("Available networks: ");
  for(int i=0; i<n; ++i) {
    Serial.print("\nSSID: ");
    Serial.println(WiFi.SSID(i));

    Serial.print("Strength: ");
    Serial.println(WiFi.RSSI(i));

    Serial.print("Channel: ");
    Serial.println(WiFi.channel(i));

    Serial.print("Encryption: ");
    Serial.println(WiFi.encryptionType(i));
    delay(100);
  }
  delay(5000);
}
