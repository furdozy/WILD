
// include the library code:
#include <LiquidCrystal.h>
#include "ui.hpp"
#include "network.h"

// initialize the library with the numbers of the interface pins






void setup(){

initCursor();
//display top menu option
initLCD();

}

void loop() {
  
  if(digitalRead(UP)==LOW){
    updateUI(1);
    while(digitalRead(UP)==LOW);
  }
    
  if(digitalRead(LEFT)==LOW){
    updateUI(2);
    while(digitalRead(LEFT)==LOW);
  }
  if(digitalRead(DOWN)==LOW){
    updateUI(3);
    while(digitalRead(DOWN)==LOW);
  }
  if(digitalRead(CENTER)==LOW){
    updateUI(4);
    while(digitalRead(CENTER)==LOW);
  }
  if(digitalRead(RIGHT)==LOW){
    updateUI(5);
    while(digitalRead(RIGHT)==LOW);
  }
  delay(200);
}
