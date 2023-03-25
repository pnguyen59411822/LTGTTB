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

