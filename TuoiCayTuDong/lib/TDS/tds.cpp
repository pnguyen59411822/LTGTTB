/* ==================================================
** Libraries
**
** =============================================== */


#include "tds.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define ESP_RESOLUTION              4096

#define TDS_PIN                     34
#define TDS_VCC                     3.3

#define TDS_NUM_SAMPLE_POINTS       30

#define TDS_TIME_UPD_SAMPLE_POINTS  40
#define TDS_TIME_UPD_VALUE          1000


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


static uint16_t samplePoints[TDS_NUM_SAMPLE_POINTS];
static uint8_t  samplePoints_ind = 0;

static float tds_volt;
static float tds_value;


/* ==================================================
** Global function declaration
**
** =============================================== */


float get_tempC();
float get_medianNum(uint16_t arr[], uint8_t size);

void upd_samplePoints();
void upd_value();


/* ==================================================
** Global function definition
**
** =============================================== */


void upd_samplePoints()
{
    static uint32_t intv = millis();

    if(millis() - intv < TDS_TIME_UPD_SAMPLE_POINTS) {return;}

    samplePoints[samplePoints_ind] = analogRead(TDS_PIN);
    samplePoints_ind += 1;

    if(samplePoints_ind == TDS_NUM_SAMPLE_POINTS){ 
        samplePoints_ind = 0;
    }

    intv = millis();
}


void upd_value()
{
    static uint32_t intv = millis();

    if(millis() - intv < TDS_TIME_UPD_VALUE) {return;}
      
    tds_volt = get_medianNum(samplePoints, TDS_NUM_SAMPLE_POINTS) * (float)TDS_VCC / ESP_RESOLUTION;

    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
    float compensationCoefficient = 1.0+0.02*(get_tempC()-25.0);
    //temperature compensation
    float compensationVoltage=tds_volt/compensationCoefficient;

    //convert voltage value to tds value
    tds_value=(133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
}


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
    upd_samplePoints();

}