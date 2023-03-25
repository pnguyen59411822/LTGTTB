

/* ==================================================
** Library
**
** =============================================== */


#include <Arduino.h>

#include "log_service.h"
#include "I2C_service.h"
#include "SPI_service.h"
#include "DHT_service.h"
#include "BMP280.h"
#include "soil_moisture.h"


/* ==================================================
** Main
**
** =============================================== */


void setup() 
{
  Log_init();
  I2C_init();
  I2C_scan();
  DHT_init();
  BMP280_init();
  SM_init();
}


void loop() 
{
  DHT_read();

  static uint32_t intv = millis();
  if(millis() - intv < 2000) {return;}

  DHT_print();
  BMP280_print();
  SM_print();

  LOG_PRINTF("\n");
  intv = millis();
}