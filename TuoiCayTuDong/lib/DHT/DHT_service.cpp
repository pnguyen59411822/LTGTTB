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


DHT dht(DHT_PIN, DHT_TYPE);

float tempC, tempF, humidity;
float heatIndexC, heatIndexF;


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


bool DHT_read()
{
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    float h = dht.readHumidity();

    if (isnan(h) || isnan(t) || isnan(f)) {
        return false;
    }

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