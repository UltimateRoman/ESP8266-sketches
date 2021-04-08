#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "DHT.h"

#define WiFi_SSID "ssid"
#define WiFi_PWD "password"

ESP8266WebServer server(80);
DHT dht(D1, DHT11);

void setup() {
  Serial.begin(9600);
  WiFi.begin(WiFi_SSID, WiFi_PWD);
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  server.on("/", show_temp);
  server.onNotFound(handle_notFound);
  server.begin();
}

void loop() {
  server.handleClient();
}

void show_temp() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String html = "<h1>Temperature: "+String(temp)+" C </h1> <br><br> <h1>Humditity: "+String(hum)+" %</h1>";
  server.send(200, "text/html", html);
}

void handle_notFound() {
  server.send(404, "text/plain", "Not found");
}
