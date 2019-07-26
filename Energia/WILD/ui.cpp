#include "Energia.h"
#include "pages.h"
#include "custChars.h"
#include <LiquidCrystal.h>
#include "ui.hpp"
#include "network.hpp"
#include <driverlib.h>
#include "storage.h"

//non static pages
String MSGS=    "New Messages:                           Total messages:                         ";
  //row          <     row 0        ><     row 2        ><     row 1        ><     row 3        >   


//messages ram tracking variables

String messages[maxMsgs];//update for flash
int newMsgs=0;//same with this
int totalMsgs= getMessage_len()/80;//same

//initialize keyboard
const byte col1 = P8_4;
const byte col2 = P8_2;
const byte col3 = P3_6;
const byte col4 = P3_0;
const byte col5 = P3_2;

const byte row1 = P8_5;
const byte row2 = P8_3;
//const byte row3 = P3_1;
const byte row4 = P3_3;
//const byte row5 = P3_4;
const byte row6 = P3_5;
const byte row7 = P3_7;


LiquidCrystal lcd(P6_4, P6_2, P2_6, P2_5, P2_4, P2_3);
int row=0;//menu expressed as a row
int col=0;//item as col

int menuSize[4]={4,3,1,totalMsgs+1};
String dne="dne";
//define menus

//
String menus[4][maxMsgs]={{VIEW,SEND,OPT,SOS} 
                    ,{ADD,INFO,EXIT}
                    ,{MSGS}
                    ,{"                        No messages                                             "} };
                    

                    
int menuArray[4][10]={{2,-1,1,-1},
                      {-1,-1,0,-1},
                      {3}         };

//define pointers for pages




void initCursor(){
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(CENTER, INPUT_PULLUP);
}

void initUI(){
 
  newMsgs=0;//same with this
  totalMsgs= getMessage_len()/80;
  for(int i = 0; i < totalMsgs; i++)
  {
    messages[i] = readMessage(i+1);
    menus[3][i] = messages[i];
  }
  menuSize[3]=totalMsgs;
  updateMsg();





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

  delay(500);
  lcd.clear();

  lcd.clear();
  lcd.setCursor(0,0);
  lcdPage(menus[0][0]);
}

void initialize_kb()
{
  digitalWrite(col1, LOW); // turn off pullup
  digitalWrite(col2, LOW); // turn off pullup
  digitalWrite(col3, LOW); // turn off pullup
  digitalWrite(col4, LOW); // turn off pullup
  digitalWrite(col5, LOW); // turn off pullup
  
  pinMode(col1, INPUT); // High-Z
  pinMode(col2, INPUT); // High-Z 
  pinMode(col3, INPUT); // High-Z
  pinMode(col4, INPUT); // High-Z
  pinMode(col5, INPUT); // High-Z
  // Rows are inputs with pullups
  
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
//  pinMode(row3, INPUT);
  pinMode(row4, INPUT);
//  pinMode(row5, INPUT);
  pinMode(row6, INPUT);
  pinMode(row7, INPUT);

  digitalWrite(row1, HIGH); // set pullup
  digitalWrite(row2, HIGH); // set pullup
//  digitalWrite(row3, HIGH); // set pullup
  digitalWrite(row4, HIGH); // set pullup
//  digitalWrite(row5, HIGH); // set pullup
  digitalWrite(row6, HIGH); // set pullup
  digitalWrite(row7, HIGH); // set pullup

  //GPIO_setAsPeripheralModuleFunctionInputPin(
  //     GPIO_PORT_P3,GPIO_PIN5,
  //      GPIO_PRIMARY_MODULE_FUNCTION    );
  
  GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN1);
  GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN4);
  //GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5);
  
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN1);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN4);
  //GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5);
}


void updateUI(int dir){

    //right
    if(dir==5){
    col++;
    if(col>menuSize[row]-1){
      col=0;
    }
    lcd.setCursor(0,0);
    lcdPage(menus[row][col]);
    }
    
    //left
    if(dir==2){
      col--;
    
      if(col<0){
        col=menuSize[row];
        }
      lcd.setCursor(0,0);
      lcdPage(menus[row][col]);
    }
    //center button
    if(dir==4){
      if(menuArray[row][col]==-1){
      doActions(row,col);
        return;
      }
      row=menuArray[row][col];
      col=0;
      lcd.setCursor(0,0);
      lcdPage(menus[row][col]);
    }

    //up arrow
    if(dir==1){
      row==0;
      col==0;
      lcd.setCursor(0,0);
      lcdPage(menus[row][col]);
    }
}
void doActions(int row,int col){
  if(row==0&&col==1){//send message page
    doSend();
  }
}


void doSend(){
  String msg=getText(80);
  Serial.print(msg);
  //Serial.print("Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal. Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this.But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.");
  lcd.setCursor(0,0);
  lcd.print("Sending Message");
  
  lcd.setCursor(0,1);
  int e;
  for(e=0;e<20;e++){
  lcd.write("*");
  delay(100);
  }
  row=0;
  col=0;
  lcdPage(menus[row][col]);
}

void updateMsg(){//fix this
  menus[2][0]=  "New messages:     "+((String)newMsgs)+"                     Total Messages:   "+((String)totalMsgs)+"                 ";
  //row          <     row 0        >                    <     row 2        ><     row 1        >                     <     row 3        >   

}

void getMsg(){
  //populate messages with strings from memory
  for(int i = 0; i < totalMsgs; i++)
  {
    //stores current array of messages as is in memory, overwritting previous version
    messages[i] = readMessage(i+1);
  }
  
  int i;
  for(i=totalMsgs-2;i>=0;i--){
    messages[i+1]=messages[i];//push messages
    menus[3][i+1]=messages[i+1];
    }
  messages[0]=Serial.readString();//add message to the top
  menus[3][0]=messages[0];
  newMsgs++;
  saveMessage(messages[0]);
  if(totalMsgs<maxMsgs)totalMsgs++;
  menuSize[3]=totalMsgs;
  updateMsg();//fix message page
  }

  
void lcdPage(String page){
  char buf[80];
  page.toCharArray(buf,81);
  int colpos=0;
  int rowpos=0;
  for(int i = 0; i < page.length(); i++)
      { 
        rowpos = i/20;
        lcd.setCursor(colpos, rowpos);
        lcd.print(buf[i]);
        colpos++;
        if(colpos == 20)
          colpos = 0;

      }
}



String getText(int maxSize){
  //clear screen
  //while enter not pressed
  // -print chars by buttons
  //return all chars as string 
while(digitalRead(CENTER)==LOW);
  lcd.clear();

  //ui additon
  lcd.setCursor(0, 0);
  lcd.print("Please Begin Typing ");
  lcd.setCursor(0, 2);
  lcd.print("   Press Enter to");
  lcd.setCursor(0, 3); 
  lcd.print("      Continue");
  delay(1500);

  char buf[maxSize];
  byte enter = 0;
  int full = 0;
  short int pos = 0;
  char oldchr = 0;
  byte shiftlock = 0; // set/unset by pressing shift and letting it go rather than using it as a modifier for another key
  byte shiftlockchanged = 0; // helper
  unsigned long t = 0; // keypad repetition interval //formally, 'time'
  int changedisplay = 0;
  int rowpos = 0;
  int colpos = 0;
  int cursorpress = 0;

  //init buf
  for(int i = 0; i < maxSize; i++)
  {
    buf[i] = ' ';
  }
  
  initialize_kb();
  
  while(1)
  {
    if(digitalRead(CENTER)==LOW)
      cursorpress = 1;
    
    if(changedisplay == 1)
    {
      lcd.setCursor(0, 0);
      for(int i = 0; i < maxSize; i++)
      { 
        rowpos = i/20;
        lcd.setCursor(colpos, rowpos);
        lcd.print(buf[i]);
        colpos++;
        if(colpos == 20)
          colpos = 0;

      }
      colpos = 0;
      changedisplay = 0;
    }

      //stop reading once 'enter' or Center cursor key pressed
      if( enter || cursorpress)
      {
        String toSend = "";
        for(int i = 0; i < maxSize; i++)
          toSend += buf[i];

        lcd.clear();
        return toSend;
      }
   
    
      byte alt = 0; // flag for alt modifer key, unimplemented.
      byte sym = 0; // flag for symbol modifer key
      byte shift = 0; // flag for shift modifier key
      byte shl = 0; // left shift for shift lock detection
      byte shr = 0; // right shift for shift lock detection
      char chr = 0; // current character
      char symb = 0; // current symbol
     
      initialize_kb();
      pinMode(col1, OUTPUT); 
      digitalWrite(col1, LOW);
      
      if (digitalRead(row1)==0) {chr = 'Q'; symb='#';}
      if (digitalRead(row2)==0) {chr = 'W'; symb='1';}
      
      if 
      (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN1) == 0) 
      {sym = 1;}             // symbol modifier key
      
      if (digitalRead(row4)==0) {chr = 'A'; symb='*';}
      if  
            (GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN4) == 0)
      {alt = 1;}             // alt modifier key - unimplemented
      if 
      (digitalRead(row6)==0){chr = ' '; symb=' ';}
      if (digitalRead(row7)==0) {chr = '~'; symb='0';}
      
      pinMode(col1, INPUT); 
      initialize_kb();
      pinMode(col2, OUTPUT); 
      digitalWrite(col2, LOW);
      
      if (digitalRead(row1)==0) {chr = 'E'; symb='2';}
      if (digitalRead(row2)==0) {chr = 'S'; symb='4';}
      if 
      (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN1) == 0)
      {chr = 'D'; symb='5';}
      if (digitalRead(row4)==0) {chr = 'P'; symb='@';}
      if 
            (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN4) == 0)
      {chr = 'X'; symb='8';}
      if 
      (digitalRead(row6)==0){chr = 'Z'; symb='7';}
      if (digitalRead(row7)==0) {shift = 1; shl = 1;}  // shift modifier key
      
      pinMode(col2, INPUT); 
      initialize_kb();
      pinMode(col3, OUTPUT); 
      digitalWrite(col3, LOW);
     
      if (digitalRead(row1)==0) {chr = 'R'; symb='3';}
      if (digitalRead(row2)==0) {chr = 'G'; symb='/';}
      if 
            (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN1) == 0)
      {chr = 'T'; symb='(';}
      if (digitalRead(row4)==0) {shift = 1; shr = 1;}  // shift modifier key
      if  
            (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN4) == 0)
      {chr = 'V'; symb='?';}
      if 
      (digitalRead(row6)==0){chr = 'C'; symb='9';}
      if (digitalRead(row7)==0) {chr = 'F'; symb='6';}
      
      pinMode(col3, INPUT); 
      initialize_kb();
      pinMode(col4, OUTPUT); 
      digitalWrite(col4, LOW);
     
      if (digitalRead(row1)==0) {chr = 'U'; symb='_';}
      if (digitalRead(row2)==0) {chr = 'H'; symb=':';}
      if 
      (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN1) == 0)
      {chr = 'Y'; symb=')';}
    //  if (digitalRead(row4)==0) {chr = '|'; symb='|';} // this should be a CR but I am substituting a pipe for CR in this implementation
      if (digitalRead(row4)==0) {enter = 1;} // enter key
      if 
            (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN4) == 0)
      {chr = 'B'; symb='!';}
      if 
      (digitalRead(row6)==0){chr = 'N'; symb=',';}
      if (digitalRead(row7)==0) {chr = 'J'; symb=';';}
      
      pinMode(col4, INPUT); 
      initialize_kb();
      pinMode(col5, OUTPUT); 
      digitalWrite(col5, LOW);
      
      if (digitalRead(row1)==0) {chr = 'O'; symb='+';}
      if (digitalRead(row2)==0) {chr = 'L'; symb='"';}
      if 
            (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN1) == 0)
      {chr = 'I'; symb='-';}
      if (digitalRead(row4)==0) {chr = 8;}            // backspace
      if 
            (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN4) == 0)
      {chr = '$'; symb='`';}
      if 
      (digitalRead(row6)==0){chr = 'M'; symb='.';}
      if (digitalRead(row7)==0) {chr = 'K'; symb='\'';}
      
      pinMode(col5, INPUT); 
    
    
    
      if (chr != oldchr)
        if (chr==8)    // Deal with backspace  
        {
          if (pos > 0) 
          {
              buf[--pos] = ' ';
              t = millis();
              changedisplay = 1;
              
          }
        }
        else if ((full == 0) && (chr !=0))
        {

            if (sym==1) // if the symbol key is pressed, put it in the buff as a symbol
              buf[pos] = symb;
            // enter raw/upper case character if shift is selected or it is not a shiftable character
            else if (shift==1 || shiftlock==1 || chr=='$' || chr==' ' || chr=='~' || chr == 13)
              buf[pos] = chr;
            // otherwise enter as a lower case character
            else
              buf[pos] = (chr+32);    
              
            // advance end of buffer
            buf[++pos] = ' ';
            if (pos == maxSize) 
            {
              full = 1;
            }
            t = millis();
            changedisplay = 1;
          
        }
      
      // Pressing both shift keys together is taken as a shift lock operation
      
      if (shl == 1 && shr == 1 && shiftlockchanged == 0)
      {
        shiftlock = (shiftlock==0)?1:0;
        shiftlockchanged = 1;  // prevent multiple shift lock activations
      }
    
      // release shift lock multi-activation production when either shift key is released.
      if ((shl == 0) || (shr == 0))
        shiftlockchanged = 0;
        
      oldchr = chr; // remember old character so we don't have a high keyboard repeat rate
      
      // however, allow repeat if there has been no change in keypress in 200ms by clearing old character
      
      if ((millis()-t)>400)
      {
        oldchr = ' ';
        t = millis();
      }
  }

  
}
