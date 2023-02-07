#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app/leddelay";


int GET_Delay(){
    DynamicJsonDocument doc(1024);
    HTTPClient http;
    const String url=baseUrl;
    http.begin(url);
    Serial.println("Getting Delay value");
    int httpCode = http.GET();
    if (httpCode>=200&&httpCode<300) {
        String payload = http.getString();
        Serial.println(payload);
        deserializeJson(doc, payload);
        int delay = doc["value"];
        return delay;
    }
    http.end();
}
void Connect_Wifi(){
    WiFi.begin("OPPO_KUY", "obbopass");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());
}