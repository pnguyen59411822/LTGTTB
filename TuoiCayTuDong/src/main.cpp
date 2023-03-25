

/* ==================================================
** Library
**
** =============================================== */


#include <Arduino.h>

#include "log_service.h"
#include "DHT_service.h"


/* ==================================================
** Main
**
** =============================================== */


void setup() 
{
  Log_init();
  DHT_init();
}


void loop() 
{
  DHT_read();

  static uint32_t intv = millis();
  if(millis() - intv < 2000) {return;}

  DHT_print();
  intv = millis();
}