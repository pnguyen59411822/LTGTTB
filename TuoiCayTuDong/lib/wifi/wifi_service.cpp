/* ==================================================
** Libraries
**
** =============================================== */


#include "wifi_service.h"

#ifdef ESP32
#include "WiFi.h"
#endif

#ifdef ESP8266
#include "ESP8266WiFi.h"
#endif


/* ==================================================
** Macro definition
**
** =============================================== */


#define WIFI_DEFAULT_SSID           "My WiFi"
#define WIFI_DEFAULT_PASS           ""

#define WIFI_LENGTH_PASS_MIN        8


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


static bool pass_is_valid(const char* pass);


/* ==================================================
** Static function declaration
**
** =============================================== */


bool pass_is_valid(const char* pass)
{
    size_t len = strlen(pass);

    if(len == 0)                    {return true;}
    if(len >= WIFI_LENGTH_PASS_MIN) {return true;}

    return false;
}


/* ==================================================
** Static function definition
**
** =============================================== */


//


/* ==================================================
** Extern function definition
**
** =============================================== */


void WiFi_init()
{

}

