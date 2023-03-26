/* ==================================================
** Libraries
**
** =============================================== */


#include "ph.h"

#include "DFRobot_PH.h"

#include "DHT_service.h"
#include "BMP280.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define ESP_RESOLUTION      4095

#define PH_PIN              35
#define PH_VCC              5000

#define PH_TIME_UPDATE      1000


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
** Global variables
**
** =============================================== */


static DFRobot_PH ph;

static float volt, ph_val,tempC = 25;


/* ==================================================
** Global function declaration
**
** =============================================== */


void upd_tempC();


/* ==================================================
** Global function definition
**
** =============================================== */


void upd_tempC()
{
    if(!isnan(DHT_get_temp())) 
    {
        tempC = DHT_get_temp();
        return;
    }

    if(!isnan(BMP280_get_tempC()))
    {
        tempC = BMP280_get_tempC();
        return;
    }

    tempC = 25;
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void PH_init()
{
    ph.begin();
}


float PH_get_val()
{
    return ph_val;
}


void PH_upd()
{
    static uint32_t intv = millis();

    ph.calibration(volt, tempC);

    if(millis() - intv < PH_TIME_UPDATE) {return;}
    intv = millis();

    upd_tempC();
    volt   = (float)analogRead(PH_PIN) / ESP_RESOLUTION * PH_VCC;
    ph_val = ph.readPH(volt, tempC);
}


void PH_print(bool update)
{
    if(update){
        LOG_U("[PH] val: %2.2f | temp: %3.2f ºC", ph_val, tempC);
        return;
    }
    
    LOG_I("[PH] val: %2.2f | temp: %3.2f ºC", ph_val, tempC);
}