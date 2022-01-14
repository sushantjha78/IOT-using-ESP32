// Needed for atoi()
#include <stdlib.h>

#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif
static const uint8_t buf_len = 20;
static const int led_pin = 2;

static int led_delay = 500;   // ms


// Task: Blink LED at rate given by the user
void FlickerLED(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
  }
}



void serialIN(void *parameters) {

  char c;
  char buf[buf_len];
  uint8_t idx = 0;

  // Clear whole buffer
  memset(buf, 0, buf_len);

  // Loop forever
  while (1) {

    // Read characters from serial
    if (Serial.available() > 0) {
      c = Serial.read();

      // Update delay variable and reset buffer if we get a newline character
      if (c == '\n') {
        led_delay = atoi(buf);
        Serial.print("Updated LED delay to: ");
        Serial.println(led_delay);
        memset(buf, 0, buf_len);
        idx = 0;
      } else {
        
        // Only append if index is not over message limit
        if (idx < buf_len - 1) {
          buf[idx] = c;
          idx++;
        }
      }
    }
  }
}



void setup() {
  pinMode(led_pin, OUTPUT);

  // Configure serial and wait a second
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("Multi-task LED");
  Serial.println("Delay time in milli seconds");

  // Start blink task
  xTaskCreatePinnedToCore(  
            FlickerLED,      
            "Flicker LED",   
            1024,           
            NULL,           
            1,              
            NULL,           
            app_cpu);       
            
  // Start serial read task
  xTaskCreatePinnedToCore(  
            serialIN,     
            "Seial in",  
            1024,           
            NULL,           
            1,              
            NULL,           
            app_cpu);       

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // looping in setup itself.
}
