int c1 = 0;
int c2 = 0;
void t1(void *par){
  for(;;){
    Serial.print("Task1 running on core ");
    Serial.println(xPortGetCoreID());
    Serial.print("Task 1 count:");
    Serial.print(c1++);
    Serial.println();
    vTaskDelay(1000);
  }
}

void t2(void *par){
  for(;;){
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);
  }
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  xTaskCreatePinnedToCore(
    t1,       // Task function
    "Task 1", // Task Name
    1000,     // Stack size  
    NULL,     // Parameter for the task
    1,        // Priority, high for high no.
    NULL,     // Task handle
    0);       // Core

 xTaskCreatePinnedToCore(
    t2,       // Task function
    "Task 2", // Task Name
    1000,     // Stack size  
    NULL,     // Parameter for the task
    1,        // Priority, high for high no.
    NULL,     // Task handle
    1);       // Core
} 
void loop() {
  // put your main code here, to run repeatedly:
}
