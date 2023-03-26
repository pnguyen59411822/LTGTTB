#ifndef DHT_service_h
#define DHT_service_h


/* ==================================================
** Libraries
**
** =============================================== */


#include <Arduino.h>

#include "log_service.h"


/* ==================================================
** Macro definition
**
** =============================================== */


//


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern function declaration
**
** =============================================== */


void DHT_init();
void DHT_reinit();
bool DHT_read();

float DHT_get_temp(bool celcius=true);
float DHT_get_humidity();
float DHT_get_heatIndex(bool celcius=true);

void DHT_print(bool update=false);


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif