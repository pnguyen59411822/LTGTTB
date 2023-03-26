/* ==================================================
** Libraries
**
** =============================================== */


#include "ph.h"

#include "DFRobot_PH.h"


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


DFRobot_PH ph;

float volt, ph_val,tempC = 25;


/* ==================================================
** Global function declaration
**
** =============================================== */


//


/* ==================================================
** Global function definition
**
** =============================================== */


//


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

    volt   = (float)analogRead(PH_PIN) / ESP_RESOLUTION * PH_VCC;
    tempC  = 25;
    ph_val = ph.readPH(volt, tempC);
}


void PH_print(bool update)
{
    if(update){
        LOG_U("[PH] val: %2.2f", ph_val);
        return;
    }
    
    LOG_I("[PH] val: %2.2f", ph_val);
}