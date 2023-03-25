/* ==================================================
** Libraries
**
** =============================================== */


#include "BMP280.h"

#include <Adafruit_BMP280.h>


/* ==================================================
** Macro definition
**
** =============================================== */


#define BMP280_I2C
// #define BMP280_SPI


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


#ifdef BMP280_I2C
Adafruit_BMP280 bmp;

#else
#endif

float pressure_seaLevel = 1013.25;


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


void BMP280_init()
{
    LOG_I("\n[BMP280] start initing");

    uint32_t status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);

    if (!status) 
    {
        LOG_E("[BMP280] Could not find a valid BMP280");
        
        LOG_PRINTF("SensorID was: %#x\n", bmp.sensorID());
        LOG_PRINTF("\t\t ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        LOG_PRINTF("\t\t ID of 0x56-0x58 represents a BMP 280,\n");
        LOG_PRINTF("\t\t ID of 0x60 represents a BME 280.\n");
        LOG_PRINTF("\t\t ID of 0x61 represents a BME 680.\n");
    }

    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


    LOG_I("[BMP280] end initing\n");
}


void BMP280_read()
{
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);
}


float BMP280_get_tempC()
{
    return bmp.readTemperature();
}


float BMP280_get_pressure()
{
    return bmp.readPressure();
}


float BMP280_get_altitude()
{
    return bmp.readAltitude(pressure_seaLevel);
}


void BMP280_set_seaLevelPressure(float pressure)
{
    pressure_seaLevel = pressure;
}


void BMP280_print(bool update)
{
    float tempC = bmp.readTemperature();
    float press = bmp.readPressure();
    float alt   = bmp.readAltitude(pressure_seaLevel);

    if(update){
        LOG_U("[BMP280] temp: %3.2f | pressure: %3.2f | alt: %3.2f", tempC, press, alt);
        return;
    }
    
    LOG_I("[BMP280] temp: %3.2f | pressure: %3.2f | alt: %3.2f", tempC, press, alt);
}