// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.
#include <Arduino.h>
//T0 not work
//T1 max 51 min 0
//T2 max 55 min 23
//T3 max 50 min 16
//T7 max 59 min 14


void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
}
void loop()
{
  Serial.print(touchRead(T3));  // get value using T0
  Serial.print(" ");
  Serial.println(millis());
  delay(100);
}

//const int ledPin =  26;      // the number of the LED pin
//const int threshold =  40;      // the number of the LED pin
//int ledState = LOW;             // ledState used to set the LED
//void setup() {
//  // put your setup code here, to run once:
//  //pinMode(ledPin, OUTPUT);
//  Serial.begin(115200);
//  touchAttachInterrupt(T7 , click , threshold );
//}
//void loop() {    
//  Serial.println( touchRead(T) );
//  delay(200);
//}
//void click () {
//  Serial.println("click!");
//}