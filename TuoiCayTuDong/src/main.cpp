

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
#include "ph.h"
#include "tds.h"


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
  PH_init();
  TDS_init();
}


void loop() 
{
  DHT_reinit();
  BMP280_reinit();

  DHT_read();
  PH_upd();
  TDS_read();

  static uint32_t intv = millis();
  if(millis() - intv < 2000) {return;}

  LOG_PRINTF("\n");
  DHT_print();
  BMP280_print();
  SM_print();
  PH_print();
  TDS_printf();

  LOG_PRINTF("\n");
  intv = millis();
}