#include "FirebaseESP8266.h"
#include<ESP8266WiFi.h>

#define FIREBASE_HOST "URL"
#define FIREBASE_AUTH "token"
#define WIFI_SSID "SSID"
#define WIFI_PWD "Password"

#define led D0

FirebaseData fData;
FirebaseData lData;

FirebaseJson json;

void setup() {  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.print("Connected. \nIP: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);  
}

void loop() {
  float tRead = analogRead(A0);
  float t = (tRead/10.24)*3.3;
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");

  if (Firebase.setFloat(fData, "/ProjectX-Node/temp", t))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + fData.dataPath());
    Serial.println("TYPE: " + fData.dataType());
    Serial.println("ETag: " + fData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + fData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  
  if (Firebase.getString(lData, "/ProjectX-Node/led")){
    Serial.println(lData.stringData());
    if (lData.stringData()=="1") {
      digitalWrite(led, LOW);
    }
    else if (lData.stringData()=="0"){
      digitalWrite(led, HIGH);
    }
  }
  delay(100);
}
