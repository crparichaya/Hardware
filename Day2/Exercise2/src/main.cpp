#include <Arduino.h>

#define RED 12 
TaskHandle_t RedLight = NULL;

void loop() {
  // put your main code here, to run repeatedly:
}

void Blink_LED(void *param){
    while(1){
        digitalWrite(RED, 1);
        vTaskDelay(500/portTICK_PERIOD_MS);
        digitalWrite(RED, 0);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void setup(){
    pinMode(RED, OUTPUT);
    xTaskCreatePinnedToCore(Blink_LED, "task_LED", 1000, NULL, 1, &RedLight, 0);
}

