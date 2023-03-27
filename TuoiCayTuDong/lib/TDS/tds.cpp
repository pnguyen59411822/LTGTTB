/* ==================================================
** Libraries
**
** =============================================== */


#include "tds.h"

#include "DHT_service.h"
#include "BMP280.h"
#include "sort_lsd.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define ESP_RESOLUTION              4096

#define TDS_NUM                     2
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
** Static variables
**
** =============================================== */


static const uint8_t TDS_PINS[TDS_NUM] = {34, 35};

static uint16_t samplePoints[TDS_NUM][TDS_NUM_SAMPLE_POINTS];
static uint8_t  samplePoints_ind[TDS_NUM];

static float tds_volt[TDS_NUM];
static float tempC[TDS_NUM];
static float tds_value[TDS_NUM];


/* ==================================================
** Static function declaration
**
** =============================================== */


static float get_medianNum(uint16_t arr[], uint8_t size);

static void upd_samplePoints();
static void upd_volt(uint8_t index);
static void upd_tempC(uint8_t index);
static void upd_value();


/* ==================================================
** Static function definition
**
** =============================================== */


float get_medianNum(uint16_t arr[], uint8_t size)
{
    uint16_t arr_temp[size];

    for(uint8_t i=0; i<size; ++i){
        arr_temp[i] = arr[i];
    }
    
    SortLSD(arr_temp, size);

    if ((size & 1) > 0){
        return arr_temp[(size - 1) / 2];
    }

    return (arr_temp[size / 2] + arr_temp[size / 2 - 1]) / 2;
}


void upd_samplePoints()
{
    static uint32_t intv = millis();

    if(millis() - intv < TDS_TIME_UPD_SAMPLE_POINTS) {return;}

    for(uint8_t i=0; i<TDS_NUM; ++i)
    {
        samplePoints[i][samplePoints_ind[i]] = analogRead(TDS_PIN);
        samplePoints_ind[i] += 1;

        if(samplePoints_ind[i] == TDS_NUM_SAMPLE_POINTS){ 
            samplePoints_ind[i] = 0;
        }
    }

    intv = millis();
}


void upd_volt(uint8_t index)
{
    tds_volt[index] = get_medianNum(samplePoints[index], TDS_NUM_SAMPLE_POINTS) * (float)TDS_VCC / ESP_RESOLUTION;
}


void upd_tempC(uint8_t index)
{
    if(!isnan(DHT_get_temp())) 
    {
        tempC[index] = DHT_get_temp();
        return;
    }

    if(!isnan(BMP280_get_tempC()))
    {
        tempC[index] = BMP280_get_tempC();
        return;
    }

    tempC[index] = 25;
}


void upd_value()
{
    static uint32_t intv = millis();

    if(millis() - intv < TDS_TIME_UPD_VALUE) {return;}

    for(uint8_t i=0; i<TDS_NUM; ++i)
    {
        upd_volt(i);
        upd_tempC(i);

        //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
        float compensationCoefficient = 1.0+0.02*(tempC-25.0);
        //temperature compensation
        float compensationVoltage=tds_volt[i]/compensationCoefficient;

        //convert voltage value to tds value
        tds_value[i]=(133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
    }
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void TDS_init()
{
    LOG_PRINTF("\n");
    LOG_I("[TDS] start initing");

    for(uint8_t i=0; i<TDS_NUM; ++i)
    {
        pinMode(TDS_PINS[i], INPUT);

        samplePoints_ind[i] = 0;
        tds_volt[i]         = nan(NULL);
        tempC[i]            = nan(NULL);
        tds_value[i]        = nan(NULL);
    }

    LOG_I("[TDS] end initing\n");
}


void TDS_read()
{
    upd_samplePoints();
    upd_value();
}


float TDS_get_value(uint8_t index)
{
    return tds_value[index];
}


void TDS_print(bool update)
{
    if(update){
        LOG_U("[TDS] value: %4.2f ppm", tds_value);
        return;
    }
    
    LOG_I("[TDS] value: %4.2f ppm", tds_value);
}