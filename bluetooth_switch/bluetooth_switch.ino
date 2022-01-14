#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
char r;
void setup() {
// the code here runs once on boot:
SerialBT.begin("ESP-32");
pinMode(2,OUTPUT);
}

void loop() {
// the code here runs repeatedly:
r = SerialBT.read();
if (r == '1'){
  digitalWrite(2,HIGH);}
if (r == '0'){
  digitalWrite(2,LOW);}
 }
