#include <driverlib.h>
#include <rom_map.h>
#include "Energia.h"
#include <flash.h>


uint32_t id = 0x20000;
int message_len = 0;


  //code below using final variable names
String readMessage(int position)
{
//  String message = "";
  char *ptr;
  ptr = (char*) id;

  MAP_FlashCtl_unprotectSector( FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0 );
  
 

  if(message_len == 0)
  {
    MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
    String ret = "";
    return ret;
  }

  String message3 = "";

  //if entered from savemessage section
  if(position == -1)
  {
    for(int i = 0; i < message_len; i++)
    {
      //reads full messages in memory and stores in a String
      message3 += ptr[i];
    }

    //cut off excess string if max length of 800 achieved
    if( (message3.length() + 80) >= 800)
      message3 = message3.substring(0, 640);
    
    MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
  
    return message3; 
  }

  
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
  
  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
  MAP_FlashCtl_performMassErase();

  MAP_FlashCtl_programMemory (message2char, (void*) id, message_len);

  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);

}
