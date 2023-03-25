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
    dht.begin();
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
}
