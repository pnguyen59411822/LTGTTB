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


static bool ssid_is_valid(const char* ssid);
static bool pass_is_valid(const char* pass);


/* ==================================================
** Static function declaration
**
** =============================================== */


static bool ssid_is_valid(const char* ssid)
{
    return strlen(ssid)==0 ? false : true;
}


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
    if(ssid_is_valid(WIFI_DEFAULT_SSID) == false){
        LOG_E("[WiFi] SSID is empty");
        return;
    }

    if(pass_is_valid(WIFI_DEFAULT_PASS) == false){
        LOG_E("[WiFi] Password is less than 8 characters");
        return;
    }

}

