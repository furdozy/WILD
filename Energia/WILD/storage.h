#include "Energia.h"

//using FLASH_SECTOR0
String message;
uint32_t id;

void saveMessage(String message,uint32_t id);

String readMessage(uint32_t id);
