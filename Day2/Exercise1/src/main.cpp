#include <Arduino.h>
#include <Bounce2.h>
#define BUTTON 27


void setup() {
  // put your setup code here, to run once:
}

void loop() {
  int cnt = 0;
  Bounce debouncer = Bounce();
    debouncer.update();
    if ( debouncer.fell() ) { 
        cnt++;
        Serial.println(cnt);
    }
}

