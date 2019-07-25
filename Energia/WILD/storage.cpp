#include <driverlib.h>
#include <rom_map.h>
#include "Energia.h"
#include <flash.h>


uint32_t id = 0x20000;
int message_len = 0;


//code below using final variable names
String readMessage(uint32_t id)
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
  
  for(int i = 0; i < message_len; i++)
  {
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

  message += readMessage(id);
  message_len = message.length();

  char message2char[message_len];
  message.toCharArray(message2char, message_len+1);
  
  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

  //assuming free data
  //will have to add code that goes to known empty location
  //can take place outside of this code as mass erase occurs regardless
  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
  MAP_FlashCtl_performMassErase();

  MAP_FlashCtl_programMemory (message2char, (void*) id, message_len);

  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
}
