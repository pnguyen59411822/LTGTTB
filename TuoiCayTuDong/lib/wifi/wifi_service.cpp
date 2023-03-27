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


#define WIFI_DEFAULT_SSID           "My SSID"
#define WIFI_DEFAULT_PASS           ""

#define WIFI_LENGTH_PASS_MIN        8

#define WIFI_TIME_CONNECT           5000


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
    LOG_PRINTF("\n");
    LOG_I("[WiFi] start initing");

    if(ssid_is_valid(WIFI_DEFAULT_SSID) == false)
    {
        LOG_E("[WiFi] SSID is empty");
        LOG_I("[WiFi] end initing\n");
        return;
    }

    if(pass_is_valid(WIFI_DEFAULT_PASS) == false)
    {
        LOG_E("[WiFi] Password is less than 8 characters");
        LOG_I("[WiFi] end initing\n");
        return;
    }

    LOG_I("[WiFi] Connecting to '%s'", WIFI_DEFAULT_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_DEFAULT_SSID, WIFI_DEFAULT_PASS);

    for(uint8_t i=0; i<3; ++i)
    {
        uint32_t timePoint = millis();
        while((millis()-timePoint) % WIFI_TIME_CONNECT*2 < WIFI_TIME_CONNECT) {}

        if(WiFi.status() == WL_CONNECTED)
        {
            LOG_I("[WiFi] Connected");

            LOG_PRINTF("I (%.3Lf) [WiFi] IP address: ", (long double)millis()/1000);
            LOG_PRINT(WiFi.localIP());
            LOG_PRINT(F("\n"));

            LOG_I("[WiFi] end initing\n");
            return;
        }
    }

    LOG_I("[WiFi] fail to connect");
    LOG_I("[WiFi] end initing\n");
}

