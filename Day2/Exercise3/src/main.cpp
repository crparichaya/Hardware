#include <Arduino.h>
#include <Bounce2.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define GREEN 27
#define BUTTON 26


Bounce debouncer=Bounce();
TaskHandle_t Task1_t = NULL;
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


#define BLUE 5
TaskHandle_t Task2_t = NULL;
void Task2(void *param){
    while(1){
        digitalWrite(BLUE, 0);
        vTaskDelay(200/portTICK_PERIOD_MS);
        digitalWrite(BLUE, 1);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app/question";
int a,b;
String op, questionId;
TaskHandle_t Task3_get = NULL;

void GET_Task_3(void *param){
    DynamicJsonDocument doc(1024);
    HTTPClient http;
    const String url = baseUrl;
    http.begin(url);

    Serial.println("response");
    int httpResponseCode = http.GET();
    if (httpResponseCode >= 200 && httpResponseCode < 300) {
        Serial.print("HTTP ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        deserializeJson(doc, payload);

        // *** write your code here ***
        // set up JSON
        Serial.println();
        Serial.println((int)doc["a"]);
        Serial.println((int)doc["b"]);
        Serial.println((const char *)doc["op"]);
        Serial.println((const char *)doc["questionId"]);

        a = (int)doc["a"];
        b = (int)doc["b"];
        op = (const char *)doc["op"];
        questionId = (const char *)doc["questionId"];


    }else{
        Serial.print("Error ");
        Serial.println(httpResponseCode);
    }

    Serial.println("----------------------------------");

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


void GET_Task3();
int a,b;
String op,questionId;
TaskHandle_t Task3_t = NULL;
void Task3(void *param){
    int time0=millis();
    while(1){
        if(millis()-time0>5000){
            GET_Task3();
            POST_Task3();
            time0=millis();
        }
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
void POST_Task3(){
    String url="https://exceed-hardware-stamp465.koyeb.app/answer";
    String json;
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");


    DynamicJsonDocument doc(2048);
    doc["questionId"]=questionId;
    if(doc["op"]=="+"){
        doc["result"]=a+b;
    }
    if(doc["op"]=="-"){
        doc["result"]=a-b;
    }
    if(doc["op"]=="*"){
        doc["result"]=a*b;
    }
    if(doc["op"]=="/"){
        doc["result"]=a/b;
    }
    serializeJson(doc,json);
    int httpCode = http.POST(json);
    if(httpCode/100==2){
        Serial.println(http.getString());
    }else{
        Serial.println("Error somehow lol");
        Serial.println(httpCode);
        Serial.println(http.getString());
    }

}

void setup(){
    Serial.begin(115200);
    pinMode(GREEN, OUTPUT);
    Connect_Wifi();
    xTaskCreatePinnedToCore(Task1, "Task1", 1024*10, NULL, 1, &Task1_t, 0);
    xTaskCreatePinnedToCore(Task2, "Task2", 1024*10, NULL, 1, &Task2_t, 0);
    xTaskCreatePinnedToCore(GET_Task_3, "GetTask3", 1024*10, NULL, 1, &Task3_get, 0);
    debouncer.attach(BUTTON, INPUT_PULLUP);
    debouncer.interval(26);
    pinMode(BLUE, OUTPUT);

    
}

void loop(){
    
}