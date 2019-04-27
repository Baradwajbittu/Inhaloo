#include <ESP8266WiFi.h>
#include <WiFiConnector.h>
WiFiConnector *wifi;
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid     = "twevent";
const char* password = "rotc sv toad nice raze";
const char* host = "api.thingspeak.com";
const String channelsAPIKey = "0DWZR2SN1PX9AAL5"; //WRITE KEY
unsigned long myChannelNumber = 747279;
int status = WL_IDLE_STATUS;
WiFiClient client;
void updateChannels();
int readValue;
String tsData;
int c=2;

void setup(){
  Serial.begin(9600);
  ThingSpeak.begin(client);
  startWiFi();
  }

void sendAndriodValues()
{
  tsData="@&field1="+String(c)+"&field2="+String(c);
  Serial.println("uploaded");
  delay(500);
 updateChannels();
}

void updateChannels()
{

if (client.connect("api.thingspeak.com", 80))
{
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+channelsAPIKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(tsData.length());
client.print("\n\n");
client.print(tsData);

if (client.connected())
{
while(client.connected() && !client.available()) delay(10); //waits for data
while (client.connected() || client.available())
{
char charIn = client.read();

}
}
}
client.stop();
Serial.flush();
}

void startWiFi()
{
client.stop();
Serial.println();
Serial.println("Connecting to");
Serial.println(ssid);

WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

delay(1000);
}

void loop(){
    c = 123;
    sendAndriodValues();
    delay(10000);
   Serial.println(c);
   ESP.deepSleep(0);
}
