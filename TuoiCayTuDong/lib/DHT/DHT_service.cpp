/* ==================================================
** Libraries
**
** =============================================== */


#include "DHT_service.h"

#include "DHT.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define DHT_PIN             32
#define DHT_TYPE            DHT11

#define DHT_TIME_REINIT     5000


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


static DHT dht(DHT_PIN, DHT_TYPE);

static float tempC      = nan(NULL);
static float tempF      = nan(NULL);
static float humidity   = nan(NULL);
static float heatIndexC = nan(NULL); 
static float heatIndexF = nan(NULL);

static bool flg_inited = false;


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


void DHT_init()
{
    LOG_PRINTF("\n");
    LOG_I("[DHT] start initing");

    dht.begin();

    LOG_I("[DHT] end initing\n");
}


void DHT_reinit()
{
    static uint32_t intv = millis();

    if(flg_inited)                        {return;}
    if(millis() - intv < DHT_TIME_REINIT) {return;}

    DHT_init();
    intv = millis();
}


bool DHT_read()
{
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    float h = dht.readHumidity();

    if (isnan(h) || isnan(t) || isnan(f)) {
        return false;
    }

    if(!flg_inited) {flg_inited = true;}

    tempC       = t;
    tempF       = f;
    humidity    = h;

    heatIndexF  = dht.computeHeatIndex(f, h);
    heatIndexC  = dht.computeHeatIndex(t, h, false);

    return true;
}


float DHT_get_temp(bool celcius)
{
    return celcius ? tempC : tempF;
}


float DHT_get_humidity()
{
    return humidity;
}


float DHT_get_heatIndex(bool celcius)
{
    return celcius ? heatIndexC : heatIndexF;
}


void DHT_print(bool update)
{
    if(update){
        LOG_U("[DHT] Humidity: %3.2f% | Temperature: %3.2f°C  %3.2f°F | Head index: %3.2f°C  %3.2f°F", humidity, tempC, tempF, heatIndexC, heatIndexF);
        return;
    }

    LOG_I("[DHT] Humidity: %3.2f% | Temperature: %3.2f°C  %.2f°F | Head index: %3.2f°C  %3.2f°F", humidity, tempC, tempF, heatIndexC, heatIndexF);
}