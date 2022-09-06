/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#include <Arduino.h>
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266HTTPClient.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <HTTPClient.h>
#endif
#include <ArduinoJson.h>
#include <AutoConnect.h>
#include "EdgeUnified.h"

#include "LH_MENU.h"

#include "LH_GPIO.h"

#include "LH_MySQL.h"
#include "MyMqtt.h"
#include "LH_SQLC.h"

/**
 * MQTT custom Web page descriptions.
 */
const char SETTINGS_MENU[] PROGMEM = R"*(
{
  "title": "MENU Setting",
  "uri": "/menu_setting",
  "menu": true,
  "element": [
    {
      "name": "style",
      "type": "ACStyle",
      "value": "

               .noorder {
                margin: auto
              }

               .noorder label {
               display: inline-block;
               width: 10.5em;
               cursor: pointer;
               padding: 5px
              }

              .noorder input[type='text'] {
               display: inline-block;
               width: 200px;
               height: 25px;
               margin: 5px 0.3em 0 0;
               cursor: pointer;
               padding: 5px;

               background-color: #EBD7FF 
              }

              .noorder input[type='button'] {
               display: inline-block;
               width: 200px;
               height: 40px;
               margin: 5px 0.3em 0 0;
               cursor: pointer;
               padding: 5px;

               background-color: #4A2E7C 
              }"                         
    },
    {
        "name": "header",
        "type": "ACElement",
        "value": "<h3 style='text-align:center;color:#2f4f4f;margin-top:10px;margin-bottom:10px'>SYSTEM AND OPERATION</h3>"
    },
    {
      "name": "caption",
      "type": "ACText",
      "value": "MENU SYSTEM",
      "style": "text-align:center;font-family:serif;color:#176499;"
    },
    {
      "name": "newline",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "LH_HOSTNAME",
      "type": "ACInput",
      "label": "LH HostName",
      "pattern": "",
      "value": "",
      "placeholder": "Recommended",
      "global": true
    },
    {
      "name": "Use_MySQL",
      "type": "ACCheckbox",
      "value": "Use_MySQL",
      "label": "Use MySQL",
      "checked": false
    },
    {
      "name": "Use_HOMEKIT",
      "type": "ACCheckbox",
      "value": "Use_HOMEKIT",
      "label": "Use HomeKit",
      "checked": false
    },
    {
      "name": "Use_MQTT",
      "type": "ACCheckbox",
      "value": "Use_MQTT",
      "label": "Use MQTT",
      "checked": false
    },
    {
      "name": "Use_BUILTIN",
      "type": "ACCheckbox",
      "value": "Use_BUILTIN",
      "label": "Use BUILTIN",
      "checked": false
    },
    {
      "name": "Use_SQLC",
      "type": "ACCheckbox",
      "value": "Use_SQLC",
      "label": "Use SQLC",
      "checked": false
    },
    {
      "name": "newline1",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "COMAND",
      "type": "ACInput",
      "value": "",
      "placeholder": "",
      "label": "COMAND: "
    },
    {
      "name": "newline2",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "SEND",
      "type": "ACSubmit",
      "value": "SEND COMAND",
      "uri": "/menu_setting"
    },
    {
      "name": "save",
      "type": "ACSubmit",
      "value": "SAVE&amp;START",
      "uri": "/menu_save"
    }
  ]
}
)*";

const char START_MENU[] PROGMEM = R"*(
{
    "title": "MENU_Setting",
    "uri": "/menu_save",
    "menu": false,
    "element": [
      {
        "name": "caption",
        "type": "ACText",
        "value": "<h4>Parameters saved OK:</h4>",
        "style": "text-align:center;color:#2f4f4f;padding:5px;"
      },
      {
      "name": "newline",
      "type": "ACElement",
      "value": "<hr>"
      },
      {
        "name": "LH_HOSTNAME",
        "type": "ACText",
        "format": "LH HOSTNAME: %s",
        "posterior": "br",
        "global": true
      },
      {
        "name": "COMAND",
        "type": "ACText",
        "format": "COMAND: %s",
        "posterior": "br",
        "global": true
      },
      {
        "name": "Use_MySQL",
        "type": "ACText",
        "format": "Use_MySQL: %s",
        "posterior": "br",
        "global": true
      },
      {
        "name": "Use_HOMEKIT",
        "type": "ACText",
        "format": "Use_HOMEKIT: %s",
        "posterior": "br",
        "global": true
      },
      {
        "name": "Use_MQTT",
        "type": "ACText",
        "format": "Use_MQTT: %s",
        "posterior": "br",
        "global": true
      },
      {
        "name": "Use_BUILTIN",
        "type": "ACText",
        "format": "Use_BUILTIN: %s",
        "posterior": "br",
        "global": true
      },
      {
        "name": "Use_SQLC",
        "type": "ACText",
        "format": "Use_SQLC: %s",
        "posterior": "br",
        "global": true
      },
      {
      "name": "BACK",
      "type": "ACSubmit",
      "value": "BACK",
      "uri": "/menu_setting"
      },
      {
        "name": "Reset",
        "type": "ACSubmit",
        "value": "Reset Board",
        "uri": "/_ac/reset"
      }
    ]
}
)*";

const char CLEAR_MENU[] PROGMEM = R"*(
{
  "title": "MENU Setting",
  "uri": "/MENU_clear",
  "menu": false,
  "response": false
}
)*";

const char STOP_MENU[] PROGMEM = R"*(
{
  "title": "MENU Setting",
  "uri": "/MENU_stop",
  "menu": false,
  "response": false
}
)*";

/**
 * Edge entities
 */
EdgeDriver<MENU_t>  menu(startMENU, processMENU, endMENU);

/**
 * Instance responsible for implementation of various IOs dependent on EdgeDriver.
 */
extern WebServer  server;
extern AutoConnect portal;
//WiFiClient    wifiClient;

// AutoConnectAux handler. Transfer EdgeData to AutoConnectElement values
String auxMENUSetting(AutoConnectAux& aux, PageArgument& args) {

  aux["Use_MySQL"].as<AutoConnectCheckbox>().checked = menu.data.Use_MySQL;
  aux["Use_HOMEKIT"].as<AutoConnectCheckbox>().checked = menu.data.Use_HOMEKIT;
  aux["Use_MQTT"].as<AutoConnectCheckbox>().checked = menu.data.Use_MQTT;
  aux["Use_BUILTIN"].as<AutoConnectCheckbox>().checked = menu.data.Use_BUILTIN;
  aux["Use_SQLC"].as<AutoConnectCheckbox>().checked = menu.data.Use_SQLC;


  aux["LH_HOSTNAME"].as<AutoConnectInput>().value = menu.data.LH_HOSTNAME;
  aux["COMAND"].as<AutoConnectInput>().value = menu.data.COMAND;


  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxMENUStart(AutoConnectAux& aux, PageArgument& args) {

  const AutoConnectAux* requestAux = portal.aux(portal.where());

  bool checked_Use_MySQL = ((AutoConnectAux&)(*requestAux))["Use_MySQL"].as<AutoConnectCheckbox>().checked;
  menu.data.Use_MySQL = checked_Use_MySQL;
  bool checked_Use_HOMEKIT = ((AutoConnectAux&)(*requestAux))["Use_HOMEKIT"].as<AutoConnectCheckbox>().checked;
  menu.data.Use_HOMEKIT = checked_Use_HOMEKIT;
  bool checked_Use_MQTT = ((AutoConnectAux&)(*requestAux))["Use_MQTT"].as<AutoConnectCheckbox>().checked;
  menu.data.Use_MQTT = checked_Use_MQTT;
  bool checked_Use_BUILTIN = ((AutoConnectAux&)(*requestAux))["Use_BUILTIN"].as<AutoConnectCheckbox>().checked;
  menu.data.Use_BUILTIN = checked_Use_BUILTIN;
  bool checked_Use_SQLC = ((AutoConnectAux&)(*requestAux))["Use_SQLC"].as<AutoConnectCheckbox>().checked;
  menu.data.Use_SQLC = checked_Use_SQLC;

  menu.data.LH_HOSTNAME = aux["LH_HOSTNAME"].as<AutoConnectText>().value;
  menu.data.COMAND = aux["COMAND"].as<AutoConnectText>().value;

  menu.save();
  menu.start();
  //menu.end();


  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxMENUStop(AutoConnectAux& aux, PageArgument& args) {
  menu.end();
  aux.redirect("/");
  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxMENUClear(AutoConnectAux& aux, PageArgument& args) {

  aux.redirect("/");
  return String();
}

// void setup
void startMENU() {

  Serial.println("Starting MENU");

  if (menu.data.LH_HOSTNAME.length()) {
    if (!menu.data.LH_HOSTNAME.equalsIgnoreCase(String(WiFi.getHostname()))) {
      WiFi.setHostname(menu.data.LH_HOSTNAME.c_str());
      startMDNS();
    }
  }

  
}

// void loop
void processMENU() {

  //Serial.println("Starting Process MENU");

}

 
void endMENU() {
 
  Serial.println("MENU publishing stopped\n");

}


void menuSerialize(JsonObject& edgeData) {
  edgeData[F("Use_MySQL")] = menu.data.Use_MySQL;
  edgeData[F("Use_HOMEKIT")] = menu.data.Use_HOMEKIT;
  edgeData[F("Use_MQTT")] = menu.data.Use_MQTT;
  edgeData[F("Use_BUILTIN")] = menu.data.Use_BUILTIN;
  edgeData[F("Use_SQLC")] = menu.data.Use_SQLC;
  edgeData[F("LH_HOSTNAME")] = menu.data.LH_HOSTNAME;
  edgeData[F("COMAND")] = menu.data.COMAND;

}

// Deserializer: MQTT EdgeData JSON object to MQTT_t EdgeData.
void menuDeserialize(JsonObject& edgeData) {
  menu.data.Use_MySQL = edgeData[F("Use_MySQL")].as<bool>();
  menu.data.Use_HOMEKIT = edgeData[F("Use_HOMEKIT")].as<bool>();
  menu.data.Use_MQTT = edgeData[F("Use_MQTT")].as<bool>();
  menu.data.Use_BUILTIN = edgeData[F("Use_BUILTIN")].as<bool>();
  menu.data.Use_SQLC = edgeData[F("Use_SQLC")].as<bool>();
  menu.data.LH_HOSTNAME = edgeData[F("LH_HOSTNAME")].as<String>();
  menu.data.COMAND = edgeData[F("COMAND")].as<String>();

}




