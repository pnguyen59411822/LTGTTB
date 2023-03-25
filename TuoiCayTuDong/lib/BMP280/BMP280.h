#ifndef BMP280_h
#define BMP280_h


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


void BMP280_init();

float BMP280_get_tempC();
float BMP280_get_pressure();
float BMP280_get_altitude();

void BMP280_set_seaLevelPressure(float pressure);

void BMP280_print(bool update=false);


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif