/* ==================================================
** Libraries
**
** =============================================== */


#include "tds.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define TDS_PIN                 34
#define TDS_NUM_SAMPLE_POINT    30


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


static uint16_t samplePoints[TDS_NUM_SAMPLE_POINT];
static uint8_t  samplePoints_ind = 0;


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


void TDS_init()
{
    LOG_PRINTF("\n");
    LOG_I("[TDS] start initing");

    pinMode(TDS_PIN, INPUT);

    LOG_I("[TDS] end initing\n");
}


void TDS_read()
{
    static uint32_t intv = millis();

    if(millis() - intv < 40) {return;}

    samplePoints[samplePoints_ind] = analogRead(TDS_PIN);
    samplePoints_ind += 1;

    if(samplePoints_ind == TDS_NUM_SAMPLE_POINT){ 
        samplePoints_ind = 0;
    }

    intv = millis();
}