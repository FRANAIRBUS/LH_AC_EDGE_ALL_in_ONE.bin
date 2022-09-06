/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#include <Arduino.h>
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#define mDNSUpdate()  do {MDNS.update();} while (0)
#define GET_CHIPID()    (ESP.getChipId())
#define GET_HOSTNAME()  (WiFi.hostname())
// COMUN
#include <ESP8266HTTPClient.h>
//
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#define mDNSUpdate() do {(void)0;} while(0)
#define GET_CHIPID()    ((uint16_t)(ESP.getEfuseMac()>>32))
#define GET_HOSTNAME()  (WiFi.getHostname())
// COMUN
#include <HTTPClient.h>
//#include <esp_log.h>
//
#endif


#include <AutoConnect.h>

// Include the EdgeUnified header.
#include "EdgeUnified.h"

// Include the module header for the EdgeDriver to be used.
#include "LH_MENU.h"
#include "LH_MySQL.h"
#include "LH_GPIO.h"
#include "LH_PROBES.h"
#include "MyMqtt.h"
#include "MyGpio.h"
#include "LH_SQLC.h"


/**
 * Declare required instances.
 */
WebServer   server;
AutoConnect portal(server);
WiFiClient    wifiClient;
AutoConnectConfig config;

#define USERNAME        "1111"   // For HTTP authentication
#define PASSWORD        "1111"   // For HTTP authentication

#include "LH_AC_CONF.h"

float TimerSendOKloop = 10000;
unsigned long SENDloop;


void FREE_HEAP(){

#if defined(ARDUINO_ARCH_ESP8266)
    //Serial.println("v.......v........V.........v.......v");
    Serial.printf("Free heap: %" PRIu32 "\n", ESP.getFreeHeap());
    Serial.println("");

#elif defined(ARDUINO_ARCH_ESP32)
    //Serial.println("v.......v........V.........v.......v");
    Serial.print("Free heap actual: ");
    Serial.println(esp_get_free_heap_size());
    Serial.print("Free heap minimun: ");
    Serial.println(esp_get_minimum_free_heap_size());
    Serial.print("Esp reason reset: ");
    esp_reset_reason_t reason = esp_reset_reason();
    ESP_LOGI("" , "Reset Reason : %X"  ,  reason);
    Serial.println(reason);

    switch (reason) {
        case ESP_RST_UNKNOWN:
          Serial.println("Reset reason can not be determined");
        break;

        case ESP_RST_POWERON:
          Serial.println("Reset due to power-on event");
        break;

        case ESP_RST_EXT:
          Serial.println("Reset by external pin (not applicable for ESP32)");
        break;

        case ESP_RST_SW:
          Serial.println("Software reset via esp_restart");
        break;

        case ESP_RST_PANIC:
          Serial.println("Software reset due to exception/panic");
        break;

        case ESP_RST_INT_WDT:
          Serial.println("Reset (software or hardware) due to interrupt watchdog");
        break;

        case ESP_RST_TASK_WDT:
          Serial.println("Reset due to task watchdog");
        break;

        case ESP_RST_WDT:
          Serial.println("Reset due to other watchdogs");
        break;                                

        case ESP_RST_DEEPSLEEP:
          Serial.println("Reset after exiting deep sleep mode");
        break;

        case ESP_RST_BROWNOUT:
          Serial.println("Brownout reset (software or hardware)");
        break;
        
        case ESP_RST_SDIO:
          Serial.println("Reset over SDIO");
        break;
        
        default:
        break;
    }
    Serial.println("");

#endif

}



void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("Start");

  
  LH_AC_SETUP();


  menu.autoRestore(true);
  menu.serializer(menuSerialize, menuDeserialize, 512);
  Edge.attach(menu);
  Edge.join(FPSTR(SETTINGS_MENU), auxMENUSetting);
  Edge.join(FPSTR(START_MENU), auxMENUStart);
  Edge.join(FPSTR(CLEAR_MENU), auxMENUClear);
  Edge.join(FPSTR(STOP_MENU), auxMENUStop);


  lh_gpio.autoRestore(true);
  Edge.attach(lh_gpio);
  Edge.join(FPSTR(SETTINGS_LH_GPIO), aux_LH_GPIOSetting);
  Edge.join(FPSTR(START_LH_GPIO), aux_LH_GPIOApply);
  //Edge.join(FPSTR(START_GPIO), auxGPIOStart);

   
  probes.autoRestore(true);
  //probes.serializer(probesSerialize, probesDeserialize, 512);
  Edge.attach(probes);
  Edge.join(FPSTR(SETTINGS_LH_PROBES), aux_LH_PROBES_Setting);
  Edge.join(FPSTR(START_LH_PROBES), aux_LH_PROBES_Start);
  Edge.join(FPSTR(CLEAR_LH_PROBES), aux_LH_PROBES_Clear);
  Edge.join(FPSTR(STOP_LH_PROBES), aux_LH_PROBES_Stop);
  


if (menu.data.Use_MySQL){

  mysql.autoRestore(true);
  mysql.serializer(mysqlSerialize, mysqlDeserialize, 512);
  Edge.attach(mysql);
  Edge.join(FPSTR(SETTINGS_MySQL), auxMySQLSetting);
  Edge.join(FPSTR(START_MySQL), auxMySQLStart);
  Edge.join(FPSTR(CLEAR_MySQL), auxMySQLClear);
  Edge.join(FPSTR(STOP_MySQL), auxMySQLStop);
}


if (menu.data.Use_MQTT){

  mqtt.autoRestore(true);
  mqtt.serializer(mqttSerialize, mqttDeserialize, 512);
  Edge.attach(mqtt);
  Edge.join(FPSTR(SETTINGS_MQTT), auxMQTTSetting);
  Edge.join(FPSTR(START_MQTT), auxMQTTStart);
  Edge.join(FPSTR(CLEAR_MQTT), auxMQTTClear);
  Edge.join(FPSTR(STOP_MQTT), auxMQTTStop);

}


if (menu.data.Use_SQLC){

  sqlc.autoRestore(true);
  sqlc.serializer(sqlcSerialize, sqlcDeserialize, 512);
  Edge.attach(sqlc);
  Edge.join(FPSTR(SETTINGS_SQLC), auxSQLCSetting);
  Edge.join(FPSTR(START_SQLC), auxSQLCStart);
  Edge.join(FPSTR(CLEAR_SQLC), auxSQLCClear);
  Edge.join(FPSTR(STOP_SQLC), auxSQLCStop);

}



if (menu.data.Use_BUILTIN){

  gpio.autoRestore(true);
  Edge.attach(gpio);
  Edge.join(FPSTR(SETTINGS_GPIO), auxGPIOSetting);
  Edge.join(FPSTR(BLINKING_GPIO), auxGPIOApply);


}


  server.on("/", handleRoot);
  portal.begin();


  if (portal.begin()) {
    //saveCredentials(CREDENTIAL_OFFSET, CREDENTIAL_DIR, CREDENTIAL_FILEPREFIX);

  }


}

void loop() {


  mysql.enable(menu.data.Use_MySQL);

  //homekit.enable(menu.data.Use_HOMEKIT);

  mqtt.enable(menu.data.Use_MQTT);

  gpio.enable(menu.data.Use_BUILTIN);

  sqlc.enable(menu.data.Use_SQLC);
  
  
  Edge.process(portal);
  mDNSUpdate();
  portal.handleClient();

  


  if (millis() - SENDloop > TimerSendOKloop) {
        
    //Serial.println("---------------------SYSTEM OK OK OK--------------------------");
    //Serial.print("Free heap: ");
    //Serial.println(ESP.getFreeHeap());
    
    SENDloop = millis();
    }
 
}



