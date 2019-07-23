       #define LED RED_LED
#define LED2 GREEN_LED

#define DOWN P4_0
#define RIGHT P4_1
#define UP P4_2
#define ENTER P4_3
#define LEFT P4_4

//#include <EEPROM.h>

void setup() {

pinMode(LED, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LEFT, INPUT_PULLUP);
pinMode(RIGHT, INPUT_PULLUP);
pinMode(DOWN, INPUT_PULLUP);
pinMode(UP, INPUT_PULLUP);
pinMode(ENTER, INPUT_PULLUP);

  
  // put your setup code here, to run once:

}

void loop() {
  if(digitalRead(LEFT)==LOW) digitalWrite(LED,HIGH);
  if(digitalRead(UP)==LOW) digitalWrite(LED,LOW);
  if(digitalRead(RIGHT)==LOW) digitalWrite(LED2,HIGH);
  if(digitalRead(DOWN)==LOW) digitalWrite(LED2,LOW);
  if(digitalRead(ENTER)==LOW) {
    digitalWrite(LED2,HIGH);
    digitalWrite(LED,HIGH);
  }
  // put your main code here, to run repeatedly: 
  
}
