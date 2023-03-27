/* ==================================================
** Libraries
**
** =============================================== */


#include "I2C_service.h"


/* ==================================================
** Macro definition
**
** =============================================== */


//


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


//


/* ==================================================
** Static function declaration
**
** =============================================== */


//


/* ==================================================
** Static function definition
**
** =============================================== */


//


/* ==================================================
** Extern function definition
**
** =============================================== */


void I2C_init()
{
    #ifndef I2C_ENABLE_CUSTOM_PINS
    Wire.begin();

    #else
    Wire.begin(I2C_SDA, I2C_SCL);
    
    #endif
}


void I2C_scan()
{
    LOG_PRINTF("\n");
    LOG_I("[I2C] scanning ...");

    uint8_t numDev = 0;

    for(uint8_t addr=1; addr<127; ++addr)
    {
        Wire.beginTransmission(addr);
        uint8_t err = Wire.endTransmission();

        if(err == 0){
            LOG_I("[I2C] found device at: %#x", addr);
            numDev ++;
            continue;
        }

        if(err == 4){
            LOG_E("[I2C] unknow error at: %#x", addr);
            continue;
        }
    }

    if(numDev == 0){
        LOG_E("[I2C] No device found");
        LOG_PRINTF("\n");
        return;
    }

    LOG_I("[I2C] end scanning\n");
}

