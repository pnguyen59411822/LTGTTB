#ifndef soil_moisture_h
#define soil_moisture_h


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


void  SM_init();

float SM_get_raw();
float SM_get_percent();

void SM_set_rawMin(int raw);
void SM_set_rawMax(int raw);

void SM_print(bool update=false);


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif