//#include <driverlib.h>
//#include <rom_map.h>
//#include "Energia.h"
//#include <flash.h>
//
//
////String readMessage()
////{
////
////  String *ptr;
////  ptr = (String*)0x20000;
////
////  MAP_FlashCtl_unprotectSector( FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0 );
////  
////  String message = ptr[0];
////  for(int i = 1; i != -1; i++)
////  {
////    message += ptr[i];
////
////    if(ptr[i] == '\0')
////      i = -1;
////  }
////
////  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
////
////  return message;
////}
//
//
////code below using final variable names
//String readMessage(uint32_t id)
//{
////  String message = "";
//  String *ptr;
//  ptr = (String*) id;
//
//  MAP_FlashCtl_unprotectSector( FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0 );
//  
//  
//  String message3 = ptr[0];
//  for(int i = 1; i <= message_len; i++)
//  {
//    message3 += ptr[i];
//
//  }
//  
//  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
//
//  return message3;
//}
//
//
//
////void saveMessage()
////{
////  String message2 = "";
////  id = 0x0 + 0x20000; //starting at initial message position in BANK1
////  message2 += readMessage(id);
////  
////  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
////  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
////
////  //assuming free data
////  //will have to add code that goes to known empty location
////  //can take place outside of this code as mass erase occurs regardless
////  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
////  MAP_FlashCtl_performMassErase();
////
////  MAP_FlashCtl_programMemory (&message2, (void*) 0x20000, message2.length()+1 );
////
////  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
////
////}
//
//
////code below using final variable names
//void saveMessage(String message, uint32_t id)
//{
//  String message2 = "";
//  id = 0x0 + 0x20000; //starting at initial message position in BANK1
//  message2 += readMessage(id);
//  
//  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
//  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
//
//  //assuming free data
//  //will have to add code that goes to known empty location
//  //can take place outside of this code as mass erase occurs regardless
//  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
//  MAP_FlashCtl_performMassErase();
//
//  MAP_FlashCtl_programMemory (&message2, (void*) id, message2.length()+1 );
//
//  MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
//
//}
