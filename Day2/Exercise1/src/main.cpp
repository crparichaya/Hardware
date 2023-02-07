#include <Arduino.h>

#define RED 12 

void task_LED(void *param){
    while(1){
        int v=sin(millis()/200.0)*127+128;
        analogWrite(RED, v);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
TaskHandle_t TaskLED=NULL;
void setup() {
    pinMode(RED,OUTPUT);
    xTaskCreatePinnedToCore(task_LED, "task_LED", 1000, NULL, 1, &TaskLED, 0);
}

void loop() {
  
}