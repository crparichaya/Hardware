#include <Arduino.h>
#include <Bounce2.h>
#define BUTTON 26
Bounce debouncer = Bounce();
int cnt = 0;

#define RED 12 

void task_LED(void *param){
    while(1){
        int v=sin(millis()/200.0)*127+128;
        analogWrite(RED, v);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

TaskHandle_t TaskButton=NULL;
void Task_Button(void *param){
    while(1){
        debouncer.update();
        if (debouncer.fell()){
          cnt++;
          Serial.println(cnt);
        }
    }
}

TaskHandle_t TaskLED=NULL;
void setup() {
    pinMode(RED,OUTPUT);
    xTaskCreatePinnedToCore(task_LED, "task_LED", 1000, NULL, 1, &TaskLED, 0);
    xTaskCreatePinnedToCore(Task_Button, "task_Button", 1000, NULL, 1, &TaskLED, 0);
    debouncer.attach(BUTTON, INPUT_PULLUP);
    debouncer.interval(26);
}

void loop(){


}

