#include "Energia.h"
#include "node.h"


void send(String msg){
  
  //string for hi 32 bits of address
  //String dHi="AT DH "+dest.SH;

  //string for low 32 bits of address
  //String dLow="AT DL "+dest.SL;

  //open the serial connection

  //send the address commands and exit command mode
//  Serial.print("+++");
  delay(50);//wait for AT mode
//  Serial.print(dHi);
//  Serial.print(dLow);
//  Serial.print("AT CN");//exit AT mode

  Serial.print(msg);

 }
