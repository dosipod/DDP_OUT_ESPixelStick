#pragma once
/*
* ESPixelStick.h
*
* Project: ESPixelStick - An ESP8266 / ESP32 and E1.31 based pixel driver
* Copyright (c) 2016 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/

#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP8266)
#	include <ESP8266WiFi.h>
#	include <ESPAsyncTCP.h>
#	include <ESP8266mDNS.h>
#	include <ESPAsyncUDP.h>
#elif defined(ARDUINO_ARCH_ESP32)
#   include <AsyncTCP.h>
#   include <AsyncUDP.h>
#   include <ESPmDNS.h>
#   include <WiFi.h>
#else
#	error "Unsupported CPU type"
#endif

#include <Ticker.h>
#include <ArduinoJson.h>

#include "memdebug.h"

extern const String VERSION;
extern const String BUILD_DATE;

#define REBOOT_DELAY    100     ///< Delay for rebooting once reboot flag is set
#define LOG_PORT        Serial  ///< Serial port for console logging

//TODO: Remove this?
// E1.33 / RDMnet stuff - to be moved to library
#define RDMNET_DNSSD_SRV_TYPE   "draft-e133.tcp"
#define RDMNET_DEFAULT_SCOPE    "default"
#define RDMNET_DEFAULT_DOMAIN   "local"
#define RDMNET_DNSSD_TXTVERS    1
#define RDMNET_DNSSD_E133VERS   1

// Configuration file params
#define CONFIG_MAX_SIZE (3*1024)    ///< Sanity limit for config file

/// Core configuration structure
typedef struct {
    // Device
    String      id;         ///< Device ID

    // Network
    String      ssid;
    String      passphrase;
    String      hostname;
    IPAddress   ip                   = (uint32_t)0;
    IPAddress   netmask              = (uint32_t)0;
    IPAddress   gateway              = (uint32_t)0;
    bool        UseDhcp              = true;  ///< Use DHCP?
    bool        ap_fallbackIsEnabled = false; ///< Fallback to AP if fail to associate?
    uint32_t    ap_timeout;          ///< How long to wait in AP mode with no connection before rebooting
    uint32_t    sta_timeout;         ///< Timeout when connection as client (station)
} config_t;

String  serializeCore          (boolean pretty = false);
void    deserializeCoreHandler (DynamicJsonDocument& jsonDoc);
bool    deserializeCore        (JsonObject & json);
boolean dsDevice               (JsonObject & json);
boolean dsNetwork              (JsonObject & json);
void    SaveConfig             ();

extern config_t config;