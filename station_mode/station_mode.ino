#include "WiFi.h"
#define LED0 2
const char* ssid = "personal";
const char* password = "0123456789";
WiFiServer server(80);
String html ="<!DOCTYPE html> \
<html> \
<body> \
<center><h1>LED control using esp as server to host a webpage</h1></center> \
<form> \
<button name=\"LED0\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED0 ON</button> \
<button name=\"LED0\" button style=\"color=red\" value=\"OFF\" type=\"submit\">LED0 OFF</button><br><br> \
</form> \
</body> \
</html>";


void Connect_WiFi()
{
WiFi.begin(ssid, password);
while(WiFi.status() != WL_CONNECTED)
{
delay(100);
}
}

void setup()
{
Serial.begin(115200);
pinMode(LED0, OUTPUT);
digitalWrite(LED0, LOW);
Serial.print("Setting soft access point mode");
WiFi.softAP(ssid, password);
IPAddress IP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(IP);
server.begin();
}


void loop()
{
WiFiClient client=server.available();
if(client)
{
String request = client.readStringUntil('\r');
if(request.indexOf("LED0=ON") != -1)digitalWrite(LED0, HIGH);
if(request.indexOf("LED0=OFF") != -1)digitalWrite(LED0, LOW);
client.print(html);
request="";
}
}
