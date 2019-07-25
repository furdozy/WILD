#include "Energia.h"
#include "pages.h"
#include "custChars.h"
#include <LiquidCrystal.h>
#include "ui.hpp"
#include "network.hpp"

//non static pages
String MSGS=    "New Messages:       Total messages:                                             ";
  //row          <     row 0        ><     row 2        ><     row 1        ><     row 3        >   


//messages ram tracking variables

String messages[maxMsgs];
int currentMsg=0;//change this to a flash address for persistence
int newMsgs=0;//same with this
int totalMsgs=0;//same


LiquidCrystal lcd(P6_4, P6_2, P2_3, P2_4, P2_5, P2_6);
int row=0;//menu expressed as a row
int col=0;//item as col

int menuSize[2]={4,3};
String dne="dne";
//define menus

//
String menus[2][4]={{VIEW,SEND,OPT,SOS} 
                    ,{ADD,INFO,EXIT,  }};
int menuArray[2][4]={{2,-1,1,-1},
                      {-1,-1,0,-1}};


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
      doActions(row,col);
      if(menuArray[row][col]==-1)return;
      row=menuArray[row][col];
      col=0;
      lcd.setCursor(0,0);
      
      lcd.print(menus[row][col]);
    }
}
void doActions(int row,int col){
  if(row==0&&col==1){//send message page
    doSend();
  }
  if(row==0&&col==0){//view message page
    //doRead();
  }
}
String getText(int maxSize){
  //clear screen
  //while enter not pressed
  // -print chars by buttons
  //return all chars as string 
}

void doSend(){
  //Serial.print(getText(80));
Serial.print("Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal. Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this.But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.");

}

void updateMsg(){
  String a="You have ";
  String b=" messages to read messages.   available, press OK                     ";
  MSGS=a.concat(((String)newMsgs).concat(b));
}

void getMsg(){
  messages[currentMsg]=Serial.readString();
  newMsgs++;
  currentMsg=(currentMsg+1)%maxMsgs;
  if(totalMsgs<10)totalMsgs++;
  updateMsg();
  }
