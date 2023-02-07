#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>


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