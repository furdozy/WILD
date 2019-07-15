
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
  attachInterrupt(digitalPinToInterrupt(bcur), left, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ccur), down, CHANGE);
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
    interrupts();
}

void up()
{
  noInterrupts();
  if(digitalRead(acur) == 0)
    lcd.print("UP");
}

void left()
{
  noInterrupts();
  if(digitalRead(bcur) == 0)
    lcd.print("LEFT");
}

void down()
{
  noInterrupts();
  if(digitalRead(ccur) == 0)
    lcd.print("DOWN");
}

void right()
{
  noInterrupts();
  if(digitalRead(dcur) == 0)
    lcd.print("RIGHT");
}

void center()
{
  noInterrupts();
  if(digitalRead(centercur) == 0)
    lcd.print("CENTER");
}
