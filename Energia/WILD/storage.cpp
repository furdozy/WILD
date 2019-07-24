#include <driverlib.h>
#include <rom_map.h>
#include "Energia.h"
#include <flash.h>


String readMessage()
{
//  String message = "";
  String *ptr;
  ptr = (String*)0x2500;

  MAP_FlashCtl_unprotectSector( FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0 );
  
  String message = ptr[0];
  for(int i = 1; i != -1; i++)
  {
    message += ptr[i];

    if(ptr[i] == '\0')
      i = -1;
  }

  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);

  return message;
}


//code below using final variable names
//String readMessage(int id)
//{
////  String message = "";
//  String *ptr;
//  ptr = (String*)location[id];
//
//  MAP_FlashCtl_unprotectSector( FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0 );
//  
//  String message = ptr[0];
//  for(int i = 1; i != -1; i++)
//  {
//    message += ptr[i];
//
//    if(ptr[i] == '\0')
//      i = -1;
//  }
//  
//  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
//
//  return message;
//}



void saveMessage()
{
  String message = "";
  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

  //assuming free data
  //will have to add code that goes to known empty location
  //can take place outside of this code as mass erase occurs regardless
  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
  MAP_FlashCtl_performMassErase();

  MAP_FlashCtl_programMemory (&message, (void*) 0x2500, message.length()+1 );

  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);

}


//code below using final variable names
//void saveMessage(String message,int id)
//{
//  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
//  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
//
//  //assuming free data
//  //will have to add code that goes to known empty location
//  //can take place outside of this code as mass erase occurs regardless
//  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
//  MAP_FlashCtl_performMassErase();
//
//  MAP_FlashCtl_programMemory (&message, (void*) location[id], message.length()+1 );
//
//  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
//
//}
