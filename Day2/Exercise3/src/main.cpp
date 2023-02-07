#include <Arduino.h>

#define BLUE 5

TaskHandle_t Task2 = NULL;

void Task_2(void *param){
    while(1){
        digitalWrite(BLUE, 0);
        vTaskDelay(200/portTICK_PERIOD_MS);
        digitalWrite(BLUE, 1);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void setup(){
    pinMode(BLUE, OUTPUT);

    xTaskCreatePinnedToCore(Task_2, "Builtin_LED", 1000, NULL, 1, &Task2, 0);
}

void loop(){
}


