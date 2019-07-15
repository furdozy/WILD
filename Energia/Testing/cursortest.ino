/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 The circuit:
 =================================
 LCD pin              Connect to
 ---------------------------------
 01 - GND             GND, pot
 02 - VCC             +5V, pot
 03 - Contrast        Pot wiper
 04 - RS              Pin8 (P2.0) 4.4
 05 - R/W             GND
 06 - EN              Pin9 (P2.1) 4.5
 07 - DB0             GND
 08 - DB1             GND
 09 - DB2             GND
 10 - DB3             GND
 11 - DB4             Pin10 (P2.2) 4.0
 12 - DB5             Pin11 (P2.3) 4.1
 13 - DB6             Pin12 (P2.4) 4.2
 14 - DB7             Pin13 (P2.5) 4.3
 15 - BL+             +5V
 16 - BL-             GND
 =================================
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P4_4, P4_5, P4_0, P4_1, P4_2, P4_3);


//init cursor pin locations
const byte acur = P5_7;
const byte bcur = P1_7;
const byte ccur = P1_6;
const byte dcur = P2_5;
const byte centercur = P3_0;

const int col = 20;
const int row = 4;

int state = 1;
volatile int changed = 0;
int state2 = 0;

//cursor
void init_cursor()
{
//  digitalWrite(acur, HIGH); // turn off pullup
//  digitalWrite(bcur, HIGH); // turn off pullup
//  digitalWrite(ccur, HIGH); // turn off pullup
//  digitalWrite(dcur, HIGH); // turn off pullup
//  digitalWrite(centercur, HIGH); // turn off pullup
  
  pinMode(acur, INPUT_PULLUP); // High-Z
  pinMode(bcur, INPUT_PULLUP); // High-Z 
  pinMode(ccur, INPUT_PULLUP); // High-Z
  pinMode(dcur, INPUT_PULLUP); // High-Z
  pinMode(centercur, INPUT_PULLUP); // High-Z

  attachInterrupt(digitalPinToInterrupt(acur), up, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bcur), down, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ccur), left, CHANGE);
  attachInterrupt(digitalPinToInterrupt(dcur), right, CHANGE);
  attachInterrupt(digitalPinToInterrupt(centercur), center, CHANGE);
}

void setup() {
 
  // set up the LCD's number of columns and rows: 
  lcd.begin(col, row);
  lcd.setCursor(0, 0);
  init_cursor();
 // state = digitalRead(bcur);
//  lcd.print(state);

}

void loop() {
    
}

void up()
{
  if(digitalRead(acur) == 0)
    lcd.print("UP");
}

void down()
{
  if(digitalRead(bcur) == 0)
    lcd.print("LEFT");
}

void left()
{
  if(digitalRead(ccur) == 0)
    lcd.print("DOWN");
}

void right()
{
  if(digitalRead(dcur) == 0)
    lcd.print("RIGHT");
}

void center()
{
  if(digitalRead(centercur) == 0)
    lcd.print("CENTER");
}
