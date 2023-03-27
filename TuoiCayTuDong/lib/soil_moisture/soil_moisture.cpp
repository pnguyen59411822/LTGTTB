/* ==================================================
** Libraries
**
** =============================================== */


#include "soil_moisture.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define SM_PIN              33
#define SM_MIN              0
#define SM_MAX              100

#define ESP_RESOLUTION      4096


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern variables
**
** =============================================== */


//


/* ==================================================
** Static variables
**
** =============================================== */


static int raw_min = 0;
static int raw_max = ESP_RESOLUTION;



/* ==================================================
** Static function declaration
**
** =============================================== */


//


/* ==================================================
** Static function definition
**
** =============================================== */


//


/* ==================================================
** Extern function definition
**
** =============================================== */


void SM_init()
{
    pinMode(SM_PIN, INPUT);
}


float SM_get_raw()
{
    return analogRead(SM_PIN);
}


float SM_get_percent()
{
    float  raw = (float)analogRead(SM_PIN);
    return raw / (raw_max-raw_min) * (SM_MAX-SM_MIN) + SM_MIN;
}


void SM_set_rawMin(int raw)
{
    raw_min = raw;
}


void SM_set_rawMax(int raw)
{
    raw_max = raw;
}


void SM_print(bool update)
{
    float raw = SM_get_raw();
    float per = SM_get_percent();

    if(update){
        LOG_U("[Soil Moisture] raw: %7.2f | percent: %7.2f", raw, per);
        return;
    }

    LOG_I("[Soil Moisture] raw: %7.2f | percent: %7.2f", raw, per);
}