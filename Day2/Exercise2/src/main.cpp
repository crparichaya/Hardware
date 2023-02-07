#include <Arduino.h>
#include <Request.h>



#define RED 12 
TaskHandle_t RedLight = NULL;
TaskHandle_t delayy = NULL;
int the_delay = 500;
int the_time = 0;


void Blink_LED(void *param){
    while(1){
        digitalWrite(RED, 1);
        vTaskDelay(the_delay/portTICK_PERIOD_MS);
        digitalWrite(RED, 0);
        vTaskDelay(the_delay/portTICK_PERIOD_MS);
    }
}
void Task_delay(void *param){
    while(1){
        if(millis()-the_time>5000){
            the_time = millis();
            the_delay = GET_Delay();
            Serial.println(the_delay);
        }
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void setup(){
    Serial.begin(115200);
    pinMode(RED, OUTPUT);
    Connect_Wifi();
    xTaskCreatePinnedToCore(Blink_LED, "task_LED", 1000, NULL, 1, &RedLight, 0);
    xTaskCreatePinnedToCore(Task_delay, "task_DELAY", 1000, NULL, 1, &delayy, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}





