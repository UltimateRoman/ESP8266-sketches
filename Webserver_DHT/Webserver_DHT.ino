#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "DHT.h"

#define WiFi_SSID "SSID"
#define WiFi_PWD "Password"

ESP8266WebServer server(80);
DHT dht(D1, DHT11);

float temp=0, hum=0;
unsigned long t1=0;

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
  dht.begin();
  get_val();
}

void loop() {
  server.handleClient();
}

void show_temp() {
  if(millis()-t1>2000) {
    get_val();
  }
  String html = "<h1>Temperature: "+String(temp)+" C </h1> <br><br> <h1>Humditity: "+String(hum)+" %</h1>";
  server.send(200, "text/html", html);
}

void handle_notFound() {
  server.send(404, "text/plain", "Not found");
}

void get_val() {
  t1 = millis();
  float t, h;
  t = dht.readTemperature();
  h = dht.readHumidity();
  if((!isnan(t))&&(!isnan(h))) {
    temp=t;
    hum=h;
  }
}
