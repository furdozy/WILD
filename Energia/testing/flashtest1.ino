#include <driverlib.h>
#include <rom_map.h>
#include <string.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(P4_4, P4_5, P4_0, P4_1, P4_2, P4_3);

void setup() {
  lcd.begin(20, 4);
  
  
  //prepare memory
  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
  MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0);
  if(MAP_FlashCtl_performMassErase())
  {
       lcd.setCursor(0, 1);
       lcd.print("ERASED");
  }
  else
  {
       lcd.setCursor(0, 1);
       lcd.print("FAILED ERASE");
  }
  
  char writetomem[4] = {'H', 'E', 'L', 'L'};
  
  String *ptr3;
  ptr3 = (String*)0x20000;
  
  
  if(!MAP_FlashCtl_programMemory ( writetomem, (void*) 0x20000, 4 ))
  {
      lcd.setCursor(0, 3);
      lcd.print("FAILED PROGRAM");
  }
  else
  {
      char *ptr2;
      ptr2 = (char*)0x20000;
      
      lcd.setCursor(0, 2);
      lcd.print(ptr2[0]);
      lcd.print(ptr2[1]);
      lcd.print(ptr2[2]);
      lcd.print(ptr2[3]);
  }
  
  if(!MAP_FlashCtl_isSectorProtected(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0))
  {
    if(MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1, FLASH_SECTOR0))
    {
        lcd.setCursor(0, 3);
        lcd.print("PROTECTED");
    }
    else
    {
        lcd.setCursor(0, 3);
        lcd.print("NOT PROTECTED");
    }
  
  }


}



void loop() {
  // put your main code here, to run repeatedly: 
  
}
