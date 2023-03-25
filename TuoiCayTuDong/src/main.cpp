

/* ==================================================
** Library
**
** =============================================== */


#include <Arduino.h>

#include "log_service.h"


/* ==================================================
** Main
**
** =============================================== */


void setup() 
{
  Log_init();
  LOG_I("Init log service");
}


void loop() 
{
  static uint32_t intv = millis();
  if(millis() - intv < 5000)
  {
    LOG_U("interval < 5000 milliseconds");
    return;
  }

  LOG_E("interval > 5000 ms");
  LOG_I("reset interval");
  intv = millis();
}