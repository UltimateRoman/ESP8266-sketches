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
    display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
    display.display();
    delay(10);
    display.clearDisplay();
  }

  display.setTextSize(2);
  display.setCursor(0,10);
  display.setTextColor(SSD1306_WHITE);
  display.print("Powered by");
  display.setCursor(48,30);
  display.print("RK");

  display.display();
  delay(1000);
}

void loop() {
  int n = WiFi.scanNetworks();

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,16);
  display.print("Found ");
  display.println(n);
  display.setCursor(0,32);
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
    String enc;
    switch(WiFi.encryptionType(i)) {
      case 2: enc="WPA/PSK";
              break;
      case 4: enc="WPA2/PSK";
              break;
      case 5: enc="WEP";
              break;
      case 7: enc="open :)";
              break;
      case 8: enc="WPA/WPA2/PSK";
              break;
              
      default: enc="N/A";
    }
    display.println(enc);
    display.setCursor(0,54);
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
