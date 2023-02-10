#include <Arduino.h>
#include <Fsm.h>
//SimpleFSM kinda good

// States สถานะ (ฟังก์ชันเข้าสถานะ, ฟังก์ชันระหว่างอยู่ในสถานะ, ฟังก์ชันขณะออกจากสถานะ)
State state_page1(&on_page1_enter, &on_page1_state, &on_page1_exit);
State state_page2(&on_page2_enter, &on_page2_state, &on_page2_exit);
State state_page3(&on_page3_enter, &on_page3_state, &on_page3_exit);

Fsm fsm(&state_page1);

void on_page1_enter(){
  Serial.println("Page 1");
  //fsm.trigger(edge_id)
}
void on_page1_state(){
  while(1){
    Serial.println("Page 1 performing");
    //fsm.trigger(1);
  }
}
void on_page1_exit(){
  Serial.println("Exit Page 1");
}
void on_page2_enter(){
  Serial.println("Page 2");
}
void on_page2_state(){
  Serial.println("Page 2 performing");
  fsm.trigger(2);
}
void on_page2_exit(){
  Serial.println("Exit Page 2");
}
void on_page3_enter(){
  Serial.println("Page 3");
}
void on_page3_state(){
  Serial.println("Page 3 performing");
  fsm.trigger(3);
}
void on_page3_exit(){
  Serial.println("Exit Page 3");
}

void setup(){
  Serial.begin(115200);
  //NULL=function to run before leaving the state
  fsm.add_transition(&state_page1, &state_page2, 1,NULL);
  fsm.add_transition(&state_page2, &state_page3, 2,NULL);
  fsm.add_transition(&state_page3, &state_page1, 3,NULL);
  Serial.println("Start");
}
void loop(){
  fsm.run_machine();
  delay(100);
}