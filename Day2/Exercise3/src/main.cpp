#include <Arduino.h>
#include <Bounce2.h>

#define GREEN 27
#define BUTTON 26

Bounce debouncer=Bounce();

void Task1(void *param){
    int task1_time_stamp=0;
    bool button_pressed=false;
    while(1){
        debouncer.update();
        if(debouncer.rose())button_pressed=false;
        if(debouncer.fell())button_pressed=true;

        if(button_pressed){
            task1_time_stamp=millis();
            digitalWrite(GREEN, HIGH);
        }else if(millis()-task1_time_stamp>5000){
            digitalWrite(GREEN, LOW);
        }
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(GREEN, OUTPUT);
    xTaskCreatePinnedToCore(Task1, "Task1", 1024*10, NULL, 1, NULL, 0);
    debouncer.attach(BUTTON, INPUT_PULLUP);
    debouncer.interval(26);
}

void loop() {

}