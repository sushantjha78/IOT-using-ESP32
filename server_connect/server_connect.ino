  #include <WiFi.h>
  #include <HTTPClient.h>

  int v;

  const char*ssid = "PERSONAL";
  const char* password = "0123456789";

  const char*serverName = "http://api.thingspeak.com/update";
  String apikey = "05DxxxxxxxxT7";

void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT);
  Serial.begin(1200);

  WiFi.begin(ssid, password);
  Serial.println("connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(serverName);
    v = touchRead(4);
    String DataSent = "api_key"+apikey+"&field1="+String(v);
    int response = http.POST(DataSent);
    Serial.print(v);
    Serial.print("Response: ");
    Serial.println(response);
    http.end();
    }
}
