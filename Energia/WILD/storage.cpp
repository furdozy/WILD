#include <driverlib.h>
#include <rom_map.h>
#include "Energia.h"
#include <flash.h>


uint32_t id = 0x20000;  //sector 0
uint32_t id2 = 0x21000; //sector 1
int message_len;


//code below using final variable names
String readMessage(int position)
{
//  String message = "";
  char *ptr;
  ptr = (char*) id;

  MAP_FlashCtl_unprotectSector( FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0 );

  String message3 = "";

  //if entered from savemessage section
  if(position == -1)
  {
    if(message_len == 0)
    {
      MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
      String ret = "";
      return ret;
    }
    
    for(int i = 0; i < message_len; i++)
    {
      //reads full messages in memory and stores in a String
      message3 += ptr[i];
    }

    //cut off excess string if max length of 800 achieved
    if( (message3.length() + 80) >= 800)
      message3 = message3.substring(0, 639);
    
    MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
  
    return message3; 
  }

  //Only readMessage called
  for(int i = 80*(position-1); i < (80+(80*(position-1))); i++)
  {
    //reads 80 characters in memory and stores them in String
    message3 += ptr[i];
  }
  
  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);

  return message3;
}


//code below using final variable names
void saveMessage(String message)
{
  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
  
  //fetch message_len
  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR1);
  char *ptr;
  ptr = (char*) id2;
  String message_len_id = "";
  if(ptr[0] == 1)
  {
    //message_len in memory. retrieve
    for(int i = 1; i <= 3; i++)
    {
      if(isDigit(ptr[i]))
        message_len_id += ptr[i];
    }
    message_len = message_len_id.toInt();
  }
  else
  {
    //no message_len stored in memory
    //write empty value to message_len_id in memory
    //current message length in memory set to 0
    //default message_len max size is 3 digits. Store 3 digits if possible. if not, full with "a" char
    message_len_id = "1";
    message_len_id += "0";
    message_len_id += "a";
    message_len_id += "a";
    char message_len_idchar[4];
    message_len_id.toCharArray(message_len_idchar, 4+1);
    
    MAP_FlashCtl_performMassErase();
    MAP_FlashCtl_programMemory (message_len_idchar, (void*) id2, 4);

    message_len = 0;
  }
  
  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR1);
  
  //extend shorter messages to a length of 80
  if(message.length() < 80)
  {
    while(message.length() < 80)
    {
      message += " ";
    }
  }

  message += readMessage(-1);
  message_len = message.length();

  char message2char[message_len];
  message.toCharArray(message2char, message_len+1);

  //sector 0
  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
  MAP_FlashCtl_performMassErase();
  MAP_FlashCtl_programMemory (message2char, (void*) id, message_len);
  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);

  //sector 1
  //store message_len in memory
  String messlen = String(message_len);
  if(messlen.length() < 2)
  {
    messlen += "a";
    messlen += "a";
  }
  else if(messlen.length() < 3)
  {
    messlen += "a";
  }
  char messlen_mem[4];
  messlen = "1" + messlen;  //remember that "1" shows that a message_len has been written to memory
  messlen.toCharArray(messlen_mem, 4+1);
  
  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR1);
  MAP_FlashCtl_performMassErase();
  MAP_FlashCtl_programMemory (messlen_mem, (void*) id2, 4);
  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR1);
}
