#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>
#include<UniversalTelegramBot.h>
#include<ArduinoJson.h>

#define WiFi_SSID "SSID"
#define WiFi_PWD "Password"

#define BotToken "TOKEN"

#define led D0

X509List cert(TELEGRAM_CERTIFICATE_ROOT);

WiFiClientSecure client;
UniversalTelegramBot bot(BotToken, client);

unsigned long prevTime=0;


void setup() {
  Serial.begin(9600);
  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);
  pinMode(led, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFi_SSID, WiFi_PWD);
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.println(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  if(millis() - prevTime > 1000) {
    int newMessages = bot.getUpdates(bot.last_message_received + 1);
    while(newMessages) {
      Serial.println("New response");
      handleMessages(newMessages);
      newMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    prevTime = millis();
  }
}

void handleMessages(int messageCount) {
  Serial.println("New messages: "+String(messageCount));
  for(int i=0; i<messageCount; ++i) {
    String chat_id = String(bot.messages[i].chat_id);
    Serial.println("from "+String(chat_id));

    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if(text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control the LED.\n\n";
      welcome += "/led_on to turn ON \n";
      welcome += "/led_off to turn OFF \n";
      welcome += "/state to request current GPIO state \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if(text == "/led_on") {
      bot.sendMessage(chat_id, "LED turned ON", "");
      digitalWrite(led, LOW);
    }
    
    if(text == "/led_off") {
      bot.sendMessage(chat_id, "LED turned OFF", "");
      digitalWrite(led, HIGH);
    }
    
    if(text == "/state") {
      if(!digitalRead(led)){
        bot.sendMessage(chat_id, "LED is ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED is OFF", "");
      }
    }
  }
}
