#include <Arduino.h>
#include <Bounce2.h>
#define BUTTON 27
#define GREEN 33
#define RED 26
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
    ledcSetup(1,5000,8);
    ledcSetup(2,5000,8);
    ledcAttachPin(GREEN, 2);
    ledcAttachPin(RED,0);
    ledcAttachPin(YELLOW,1);
    
}

void loop() {
    debouncer.update();
    if ( debouncer.fell() ) { 
        cnt++;

    if(cnt>0b111){
        cnt=0b000;
      
    }
    Serial.println(cnt);
    }
    

    int value = map(analogRead(LDR),0,4095,0,255);
    Serial.println(value);
    delay(100);


    ledcWrite(0, (cnt&0b100)==0b100?value:0);//RED
    ledcWrite(1, (cnt&0b010)==0b010?value:0);//YELLOW
    ledcWrite(2, (cnt&0b001)==0b001?value:0);//
    
}

// #define GREEN 33

// #define YELLOW 25
// #define RED 26
// void setup() {
//     pinMode(RED, OUTPUT);
//     digitalWrite(RED,0);
//     pinMode(YELLOW, OUTPUT);
//     digitalWrite(YELLOW,0);
//     pinMode(GREEN, OUTPUT);
//     digitalWrite(GREEN,0);
// }

// void loop() {
//     digitalWrite(RED,1);
//     digitalWrite(YELLOW,1);
//     digitalWrite(GREEN,1);
//     delay(500);

//     digitalWrite(RED,0);
//     digitalWrite(YELLOW,0);
//     digitalWrite(GREEN,0);
//     delay(500);
// }
