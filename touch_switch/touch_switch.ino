int V;
void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(4,INPUT);
  Serial.begin(300);

}

void loop() {
  // put your main code here, to run repeatedly:
 V = touchRead(4);
 Serial.println(V);
 if (V<80)
  digitalWrite(2,HIGH);
 else
  digitalWrite(2,LOW);
  
}
