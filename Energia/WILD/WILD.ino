
// include the library code:
#include <LiquidCrystal.h>
#include "custChars.h"
#include "network.h"
#include "pages.h"
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P6_4, P6_2, P2_3, P2_4, P2_5, P2_6);
int row=0;
int col=0;

//define menus
String menu[4]={VIEW,SEND,OPT,SOS};
//options menu
//char *options[2]={ADD,INFO};

void setup() {
//init the lcd and display welcome screen----------------
  node connected[20];
  
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








//display top menu option
lcd.clear();
lcd.setCursor(0,0);
lcd.print(menu[0]);
}

void loop() {
  
}
