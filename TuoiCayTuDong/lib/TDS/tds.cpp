/* ==================================================
** Libraries
**
** =============================================== */


#include "tds.h"

#include "DHT_service.h"
#include "BMP280.h"


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

static float tds_volt  = nan(NULL);
static float tempC     = nan(NULL);
static float tds_value = nan(NULL);


/* ==================================================
** Global function declaration
**
** =============================================== */


float get_medianNum(uint16_t arr[], uint8_t size);

void upd_samplePoints();
void upd_volt();
void upd_tempC();
void upd_value();


/* ==================================================
** Global function definition
**
** =============================================== */


float get_medianNum(uint16_t arr[], uint8_t size)
{
    uint16_t bArray[size];
    uint16_t bTab[size];

    for(uint8_t i=0; i<size; ++i){
        bArray[i] = arr[i];
    }
        
    for (byte i = 0; i<size; ++i){
        bTab[i] = bArray[i];
    }

    int i, j;
    float bTemp;
    
    for (j = 0; j < size - 1; j++) {
        for (i = 0; i < size - j - 1; i++) 
        {
            if (bTab[i] > bTab[i + 1]) {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }

    if ((size & 1) > 0){
        bTemp = bTab[(size - 1) / 2];
    }
    else {
        bTemp = (bTab[size / 2] + bTab[size / 2 - 1]) / 2;
    }

    return bTemp;
}


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


void upd_volt()
{
    tds_volt = get_medianNum(samplePoints, TDS_NUM_SAMPLE_POINTS) * (float)TDS_VCC / ESP_RESOLUTION;
}


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


void upd_value()
{
    static uint32_t intv = millis();

    if(millis() - intv < TDS_TIME_UPD_VALUE) {return;}
      
    upd_volt();
    upd_tempC();

    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
    float compensationCoefficient = 1.0+0.02*(tempC-25.0);
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
    upd_value();
}


float TDS_get_value()
{
    return tds_value;
}


void TDS_print(bool update)
{
    if(update){
        LOG_U("[TDS] value: %4.2f ppm", tds_value);
        return;
    }
    
    LOG_I("[TDS] value: %4.2f ppm", tds_value);
}