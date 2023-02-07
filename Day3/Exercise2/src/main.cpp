#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>



#define RED 12
 
TaskHandle_t RedLight = NULL;
TaskHandle_t delayy = NULL;
int the_delay = 500;
int time0 = 0;


const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";

int GET_Delay(){
    DynamicJsonDocument doc(2048);
    HTTPClient http;
    const String url=baseUrl+"/leddelay";
    http.begin(url);
    Serial.println("Getting Delay value");
    int delay=-1;
    int httpCode = http.GET();
    if (httpCode>=200&&httpCode<300) {
        String payload = http.getString();
        deserializeJson(doc, payload);
        delay = doc["value"];
    }
    return delay;
}
void Connect_Wifi(){
    WiFi.begin("OPPO_KUY", "oppopass");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());
}

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
        if(millis()-time0>5000){
            time0 = millis();
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
    xTaskCreatePinnedToCore(Blink_LED, "task_LED", 1024*10, NULL, 1, &RedLight, 0);
    xTaskCreatePinnedToCore(Task_delay, "task_DELAY", 1024*10, NULL, 1, &delayy, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
}





