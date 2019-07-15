#include "Energia.h"
#include "node.h"
#include <string.h>






int findNodes(){
  
  
  
}

int send(String msg,struct node dest){
  
  //string for hi 32 bits of address
  String dHi="AT DH "+dest.SH;

  //string for low 32 bits of address
  String dLow="AT DL "+dest.SL;

  //open the serial connection
  Serial.begin(9600);

  //send the address commands and exit command mode
  Serial.print("+++");
  delay(50);//wait for AT mode
  Serial.print(dHi);
  Serial.print(dLow);
  Serial.print("AT CN");//exit AT mode

  Serial.print(msg);

  return 1;//return statement for reading status if needed at a future date
}
