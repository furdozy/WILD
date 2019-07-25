
// include the library code:
#include <LiquidCrystal.h>
#include "ui.hpp"
#include "network.hpp"

// initialize the library with the numbers of the interface pins






void setup(){
//Serial.begin(9600);
initCursor();
//display top menu option
initLCD();

}

void loop() {
  if(Serial.available()>0){
    getMsg();
  }
  
  if(digitalRead(UP)==LOW){
    updateUI(1);
    while(digitalRead(UP)==LOW);
  delay(50);}
    
  if(digitalRead(LEFT)==LOW){
    updateUI(2);
    while(digitalRead(LEFT)==LOW);
  delay(50);}
  if(digitalRead(DOWN)==LOW){
    updateUI(3);
    while(digitalRead(DOWN)==LOW);
  delay(50);}
  if(digitalRead(CENTER)==LOW){
    updateUI(4);
    while(digitalRead(CENTER)==LOW);
    delay(50);
  }
  if(digitalRead(RIGHT)==LOW){
    updateUI(5);
    while(digitalRead(RIGHT)==LOW);
    delay(50);
  }
}
