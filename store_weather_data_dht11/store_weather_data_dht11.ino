#include "WiFi.h"
#include "ThingSpeak.h"
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define CHANNEL_ID 1550217
#define API_KEY "JRUYCT5JJPX7DLGZ"
#define WIFI_TIMEOUT_MS 10000
#define WIFI_NETWORK "PERSONAL"
#define WIFI_PASSWORD "0123456789"
#ifdef __cplusplus

WiFiClient client;

extern "C"
{
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();
void setup() {
WiFi.mode(WIFI_STA);
WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
ThingSpeak.begin(client);
Serial.begin(9600);
Serial.println(F("DHTxx test!"));
dht.begin();
}
void loop() {
  delay(2000);
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
// Read temperature as Fahrenheit (isFahrenheit = true)
float f = dht.readTemperature(true);

// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
}
// Compute heat index in Fahrenheit (the default)
float hif = dht.computeHeatIndex(f, h);
// Compute heat index in Celsius (isFahreheit = false)
float hic = dht.computeHeatIndex(t, h, false);

Serial.print(F("Humidity: "));
Serial.print(h);
Serial.print(F("%  Temperature: "));
Serial.print(t);
Serial.print(F("°C "));
Serial.print(f);
Serial.print(F("°F  Heat index: "));
Serial.print(hic);
Serial.print(F("°C "));
Serial.print(hif);
Serial.println(F("°F"));

ThingSpeak.writeField(CHANNEL_ID,2,h,API_KEY);
delay(500);
ThingSpeak.writeField(CHANNEL_ID,1,t,API_KEY);
delay(500);
}
