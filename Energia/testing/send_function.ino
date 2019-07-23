// include the library code:
#include <LiquidCrystal.h>
#include <string.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P4_4, P4_5, P4_0, P4_1, P4_2, P4_3);

//initialize keyboard
const byte col1 = P2_4;
const byte col2 = P2_7;
const byte col3 = P2_6;
const byte col4 = P5_6;
const byte col5 = P6_6;

const byte row1 = P6_7;
const byte row2 = P2_3;
const byte row3 = P5_2;
const byte row4 = P3_6;
const byte row5 = P3_7;
const byte row6 = P3_5;
const byte row7 = P5_1;





void setup() {
  

  read_keyboard(5); //max message size of 5
//
//  check_message();
//
//  send_message();
  
}

void loop() {}

//void check_message()
//{
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("Send Message?");
//  
//  //print message in buffer
//  for(int i = 1; i < row; i++)
//  { 
//    lcd.setCursor(0, i);
//    lcd.print(buf[i]);
//  }
//
//  //check for enter
//   initialize_kb();
//  pinMode(col4, OUTPUT); 
//  digitalWrite(col4, LOW);
//  while(!enter)
//  { 
//    //waiting for user to  select enter
//   if (digitalRead(row4)==0) {enter = 1;}
//  }
//}
//
//void send_message()
//{
//    lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("Sent Message!");
//  for(int i = 1; i < row; i++)
//  { 
//    lcd.setCursor(0, i);
//    lcd.print(buf[i]);
//  }
//}






char *read_keyboard(int maxSize)
{
  lcd.begin(20, 4);
  char *buf;
  buf = (char*)malloc(sizeof(char)*maxSize);
  byte enter = 0;
  int full = 0;
  short int pos = 0;
  char oldchr = 0;
  byte shiftlock = 0; // set/unset by pressing shift and letting it go rather than using it as a modifier for another key
  byte shiftlockchanged = 0; // helper
  unsigned long t = 0; // keypad repetition interval //formally, 'time'
  byte curline = 0; //FOR STARTING MESSAGE ON SECOND LINE
  int changedisplay = 0;
  int rowpos = 0;
  int colpos = 0;

  //init buf
  for(int i = 0; i < maxSize; i++)
  {
    buf[i] = 0;
  }
  
  initialize_kb();
  
  while(1)
  {
    if(changedisplay == 1)
    {
      for(int i = 0; i < maxSize; i++)
      { 
        rowpos = (int)i/20;
        lcd.setCursor(colpos, rowpos);
        lcd.print(buf[i]);
        colpos++;
        if(colpos == 20)
          colpos = 0;
      }
      changedisplay = 0;
    }

      //stop reading once 'enter' or Center cursor key pressed
      if( enter || (dir == 4))
      {
//        enter = 0;
        return buf;
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
      if (digitalRead(row3)==0) {sym = 1;}             // symbol modifier key
      if (digitalRead(row4)==0) {chr = 'A'; symb='*';}
      if (digitalRead(row5)==0) {alt = 1;}             // alt modifier key - unimplemented
      if (digitalRead(row6)==0) {chr = ' '; symb=' ';}
      if (digitalRead(row7)==0) {chr = '~'; symb='0';}
      
      pinMode(col1, INPUT); 
      initialize_kb();
      pinMode(col2, OUTPUT); 
      digitalWrite(col2, LOW);
      
      if (digitalRead(row1)==0) {chr = 'E'; symb='2';}
      if (digitalRead(row2)==0) {chr = 'S'; symb='4';}
      if (digitalRead(row3)==0) {chr = 'D'; symb='5';}
      if (digitalRead(row4)==0) {chr = 'P'; symb='@';}
      if (digitalRead(row5)==0) {chr = 'X'; symb='8';}
      if (digitalRead(row6)==0) {chr = 'Z'; symb='7';}
      if (digitalRead(row7)==0) {shift = 1; shl = 1;}  // shift modifier key
      
      pinMode(col2, INPUT); 
      initialize_kb();
      pinMode(col3, OUTPUT); 
      digitalWrite(col3, LOW);
     
      if (digitalRead(row1)==0) {chr = 'R'; symb='3';}
      if (digitalRead(row2)==0) {chr = 'G'; symb='/';}
      if (digitalRead(row3)==0) {chr = 'T'; symb='(';}
      if (digitalRead(row4)==0) {shift = 1; shr = 1;}  // shift modifier key
      if (digitalRead(row5)==0) {chr = 'V'; symb='?';}
      if (digitalRead(row6)==0) {chr = 'C'; symb='9';}
      if (digitalRead(row7)==0) {chr = 'F'; symb='6';}
      
      pinMode(col3, INPUT); 
      initialize_kb();
      pinMode(col4, OUTPUT); 
      digitalWrite(col4, LOW);
     
      if (digitalRead(row1)==0) {chr = 'U'; symb='_';}
      if (digitalRead(row2)==0) {chr = 'H'; symb=':';}
      if (digitalRead(row3)==0) {chr = 'Y'; symb=')';}
    //  if (digitalRead(row4)==0) {chr = '|'; symb='|';} // this should be a CR but I am substituting a pipe for CR in this implementation
      if (digitalRead(row4)==0) {enter = 1;} // enter key
      if (digitalRead(row5)==0) {chr = 'B'; symb='!';}
      if (digitalRead(row6)==0) {chr = 'N'; symb=',';}
      if (digitalRead(row7)==0) {chr = 'J'; symb=';';}
      
      pinMode(col4, INPUT); 
      initialize_kb();
      pinMode(col5, OUTPUT); 
      digitalWrite(col5, LOW);
      
      if (digitalRead(row1)==0) {chr = 'O'; symb='+';}
      if (digitalRead(row2)==0) {chr = 'L'; symb='"';}
      if (digitalRead(row3)==0) {chr = 'I'; symb='-';}
      if (digitalRead(row4)==0) {chr = 8;}            // backspace
      if (digitalRead(row5)==0) {chr = '$'; symb='`';}
      if (digitalRead(row6)==0) {chr = 'M'; symb='.';}
      if (digitalRead(row7)==0) {chr = 'K'; symb='\'';}
      
      pinMode(col5, INPUT); 
    
    
    
      if (chr != oldchr)
        if (chr==8)    // Deal with backspace  
        {
          if (pos > 0) // don't underflow our buffer
          {
//              if (pos==0) 
//              {
//                pos=col-1; 
//                curline--;
//              }
              buf[--pos] = 0;
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
            buf[++pos] = 0;
            if (pos == MaxSize) 
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
        oldchr = 0;
        t = millis();
      }
  }

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
  pinMode(row3, INPUT);
  pinMode(row4, INPUT);
  pinMode(row5, INPUT);
  pinMode(row6, INPUT);
  pinMode(row7, INPUT);

  digitalWrite(row1, HIGH); // set pullup
  digitalWrite(row2, HIGH); // set pullup
  digitalWrite(row3, HIGH); // set pullup
  digitalWrite(row4, HIGH); // set pullup
  digitalWrite(row5, HIGH); // set pullup
  digitalWrite(row6, HIGH); // set pullup
  digitalWrite(row7, HIGH); // set pullup
}
