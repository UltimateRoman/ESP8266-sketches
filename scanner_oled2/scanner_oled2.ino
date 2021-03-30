#include<ESP8266WiFi.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#define screenw 128
#define screenh 64

#define screenAddr 0x3C
#define OLED_RESET -1

Adafruit_SSD1306 display(screenw, screenh, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  while(!display.begin(SSD1306_SWITCHCAPVCC, screenAddr)) {
    Serial.println("SSD1306 allocation failed");
  }
  
  display.display();
  delay(3000);

  display.setRotation(2);

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.clearDisplay();
    display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
    display.display();
    delay(10);
  }

  delay(500);

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.println("Powered by");
  display.print("RK");

  display.display();
  delay(1000);
}

void loop() {
  int n = WiFi.scanNetworks();

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Found ");
  display.println(n);
  display.print("Network(s)");
  display.display();
  delay(1500);
  
  for(int i=0; i<n; ++i) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    display.print("SSID: ");
    display.println(WiFi.SSID(i));
    display.setCursor(0,16);
    display.print("Strength: ");
    display.println(WiFi.RSSI(i));
    display.setCursor(0,32);
    display.print("Encryption: ");
    display.println(WiFi.encryptionType(i));
    display.setCursor(0,48);
    display.print("Channel: ");
    display.println(WiFi.channel(i));
    display.display();
    
    delay(5000);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Scanning........");
  display.display();
  
  delay(5000);
}
