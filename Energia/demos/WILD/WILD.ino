
// include the library code:
#include <LiquidCrystal.h>
#include "custChars.h"
#include "message.h"
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P6_7, P2_3, P2_6, P2_4, P5_6, P6_6);
int row=0;
int col=0;
void setup() {
  
  Serial.begin(9600);
  
  lcd.createChar(0, topLeft);
  lcd.createChar(1, topMiddle);
  lcd.createChar(2, topRight);
  lcd.createChar(3, bottomLeft);
  lcd.createChar(4, bottomMiddle);
  lcd.createChar(5, bottomRight);
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  lcd.clear();
  int e=0;
  for(e=0;e<20;e++){
  lcd.write("*");
  delay(100);
  }
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)1);
  lcd.write((uint8_t)2);
  lcd.print("W.I.L.D. Group 10");

  lcd.setCursor(0, 1);
  lcd.write((uint8_t)3);
  lcd.write((uint8_t)4);
  lcd.write((uint8_t)5);
  lcd.print("Wilderness Info");

  delay(5000);
  lcd.clear();
}

void loop() {
   if (Serial.available()) {
    lcd.write("~");
    byte data=Serial.read();
    if((int)data==127){
      col=col-1;
      if(col==-1){
        col=19;
        row=row-1;
      }
      lcd.setCursor(col,row);
      lcd.print(' ');
      lcd.setCursor(col,row);
    }else{
    lcd.write(data);
    col=(col+1)%20;
    if(col==0)row=(row+1)%4;
    lcd.setCursor(col,row);
    }
   }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 
}
