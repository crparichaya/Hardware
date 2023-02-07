#include <Arduino.h>

#define BLUE 5

TaskHandle_t TaskA = NULL;

void Lit_LED(void *param){
    while(1){
        digitalWrite(BLUE, 0);
        vTaskDelay(200/portTICK_PERIOD_MS);
        digitalWrite(BLUE, 1);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void setup(){
    pinMode(BLUE, OUTPUT);

    xTaskCreatePinnedToCore(Lit_LED, "Builtin_LED", 1000, NULL, 1, &TaskA, 0);
}

void loop(){
}


