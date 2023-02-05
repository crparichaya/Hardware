#include <Arduino.h>
#include <Bounce2.h>
#define BUTTON 27
#define GREEN 33
#define RED 23
#define YELLOW 25
#define LDR 32
int cnt = 0;
Bounce debouncer = Bounce();//This actually using low-pass filter (according to blog)

void setup() {
    Serial.begin(115200);
    Serial.println("BUTTON");
    debouncer.attach(BUTTON, INPUT_PULLUP);
    debouncer.interval(25);
    pinMode(GREEN, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);


    ledcSetup(0, 5000, 8);
    ledcAttachPin(GREEN, 0);
    ledcAttachPin(RED,0);
    ledcAttachPin(YELLOW,0);
}

void loop() {
    debouncer.update();
    if ( debouncer.fell() ) { 
        cnt++;
        Serial.println(cnt);
    }
    if(cnt>0b111){
        cnt=0b000;
    }

    int value = map(analogRead(LDR),0,4095,0,255);


    ledcWrite(0, cnt&0b100==0b100?value:0);//RED
    ledcWrite(1, cnt&0b010==0b010?value:0);//YELLOW
    ledcWrite(2, cnt&0b001==0b001?value:0);//
    

}