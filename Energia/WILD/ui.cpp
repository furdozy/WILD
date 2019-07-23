#include "Energia.h"
#include "pages.h"
#include "custChars.h"
#include <LiquidCrystal.h>
#include "ui.hpp"


LiquidCrystal lcd(P6_4, P6_2, P2_3, P2_4, P2_5, P2_6);
int row=0;//menu expressed as a row
int col=0;//item as col

int menuSize[2]={4,3};
String dne=dne;
//define menus

//
String menus[2][4]={{VIEW,SEND,OPT,SOS} 
                    ,{ADD,INFO,EXIT,}    };
int menuArray[2][4]={{-1,-1,1,-1},{-1,-1,0,-1}};


//define pointers for pages




void initCursor(){
pinMode(LEFT, INPUT_PULLUP);
pinMode(RIGHT, INPUT_PULLUP);
pinMode(DOWN, INPUT_PULLUP);
pinMode(UP, INPUT_PULLUP);
pinMode(CENTER, INPUT_PULLUP);
}

void initLCD(){
  





//init the lcd and display welcome screen----------------
   
  
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

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menus[0][0]);
}
void updateUI(int dir){
  
    if(dir==5){
    col++;
    if(col>menuSize[row]-1){
      col=0;
    }
    lcd.setCursor(0,0);
    lcd.print(menus[row][col]);
    }
    if(dir==2){
    col--;
    
    if(col<0){
      col=menuSize[row];
      }
      lcd.setCursor(0,0);
      lcd.print(menus[row][col]);
    }
    if(dir==4){
      row=menuArray[row][col];
      col=0;
      lcd.setCursor(0,0);
      lcd.print(menus[row][col]);
    }



  
  if(dir==4){
    return;
  }
}
  
