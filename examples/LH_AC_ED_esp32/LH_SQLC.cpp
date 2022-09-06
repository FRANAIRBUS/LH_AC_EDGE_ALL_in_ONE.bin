/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#include <Arduino.h>
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#endif
#include <ArduinoJson.h>
#include <AutoConnect.h>
#include "EdgeUnified.h"
#include "LH_SQLC.h"
#include "LH_GPIO.h"



/**
 * MQTT custom Web page descriptions.
 */
const char SETTINGS_SQLC[] PROGMEM = R"*(
{
  "title": "SQLC Setting",
  "uri": "/sqlc_setting",
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
        "value": "<h3 style='text-align:center;color:#2f4f4f;margin-top:10px;margin-bottom:10px'>SERVER SQLC SETTINGS</h3>"
    },
    {
      "name": "caption",
      "type": "ACText",
      "value": "",
      "style": "font-family:serif;color:#053d76"
    },
    {
      "name": "newline",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "serverNameSQLC",
      "type": "ACInput",
      "label": "Server:",
      "pattern": "http://iot.imofrio.es/posti.php",
      "value": "",
      "placeholder": "http://server.com:3306",
      "global": true
    },
    {
      "name": "portSQLC",
      "type": "ACInput",
      "label": "Server Port:",
      "pattern": "",
      "value": "tPmAT5Ab3j7F9",
      "placeholder": "optional",
      "global": true
    },
    {
      "name": "dbnameSQLC",
      "type": "ACInput",
      "label": "Name Db:",
      "pattern": "",
      "value": "",
      "placeholder": "required",
      "global": true
    },
    {
      "name": "dbtableSQLC",
      "type": "ACInput",
      "label": "Name Table:",
      "pattern": "",
      "value": "",
      "placeholder": "required",
      "global": true
    },
    {
      "name": "usernameSQLC",
      "type": "ACInput",
      "label": "User Name:",
      "pattern": "",
      "value": "imofrio_iot",
      "placeholder": "required",
      "global": true
    },
    {
      "name": "passwordSQLC",
      "type": "ACInput",
      "label": "Password:",
      "pattern": "",
      "value": "IMOFRIO202011111111111",
      "placeholder": "required",
      "global": true
    },
    {
      "name": "sensorLocationSQLC",
      "type": "ACInput",
      "label": "Sys Location:",
      "pattern": "",
      "value": "",
      "placeholder": "optional",
      "global": true
    },
    {
      "name": "SensorNameSQLC",
      "type": "ACInput",
      "label": "System Name:",
      "pattern": "",
      "value": "",
      "placeholder": "optional",
      "global": true
    },
    {
      "name": "timerSQLC",
      "type": "ACInput",
      "label": "Timer Send:",
      "pattern": "",
      "value": "0.5",
      "placeholder": "minute",
      "global": true
    },
    {
      "name": "ValueSQLC",
      "type": "ACInput",
      "label": "ValueSQLC",
      "pattern": "",
      "value": "",
      "placeholder": "optional",
      "global": true
    },
    {
      "name": "newline2",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "stop",
      "type": "ACSubmit",
      "value": "Stop publishing",
      "uri": "/sqlc_stop"
    },
    {
      "name": "save",
      "type": "ACSubmit",
      "value": "Save&amp;Start",
      "uri": "/sqlc_start"
    }
  ]
}
)*";

const char START_SQLC[] PROGMEM = R"*(
{
  "title": "SQLC Setting",
  "uri": "/sqlc_start",
  "menu": false,
  "element": [
    {
      "name": "caption",
      "type": "ACText",
      "value": "<h4>Parameters saved as:</h4>",
      "style": "text-align:center;color:#2f4f4f;padding:5px;"
    },
    {
      "name": "serverNameSQLC",
      "type": "ACText",
      "format": "server SQLC: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "portSQLC",
      "type": "ACText",
      "format": "Server Port: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "dbnameSQLC",
      "type": "ACText",
      "format": "dbname SQLC: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "dbtableSQLC",
      "type": "ACText",
      "format": "dbtableSQLC: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "usernameSQLC",
      "type": "ACText",
      "format": "username SQLC: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "passwordSQLC",
      "type": "ACText",
      "format": "password SQLC: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "sensorLocationSQLC",
      "type": "ACText",
      "format": "sensor Location: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "SensorNameSQLC",
      "type": "ACText",
      "format": "Sensor Name: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "timerSQLC",
      "type": "ACText",
      "format": "timer SQLC: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "ValueSQLC",
      "type": "ACText",
      "format": "ValueSQLC: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "BACK",
      "type": "ACSubmit",
      "value": "BACK",
      "uri": "/sqlc_setting"
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

const char CLEAR_SQLC[] PROGMEM = R"*(
{
  "title": "SQLC Setting",
  "uri": "/sqlc_clear",
  "menu": false,
  "response": false
}
)*";

const char STOP_SQLC[] PROGMEM = R"*(
{
  "title": "SQLC Setting",
  "uri": "/sqlc_stop",
  "menu": false,
  "response": false
}
)*";

/**
 * Edge entities
 */
EdgeDriver<SQLC_t>  sqlc(startSQLC, processSQLC, endSQLC);


#include <MySQL_Generic.h>

/*
#define USING_HOST_NAME     true
#if USING_HOST_NAME
char server2[] = "myserver.com"; // change to your server's hostname/URL
#else
IPAddress server2(192, 168, 1, 2);
#endif

/*
char server3[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
uint16_t server_port = 3307;              //3306;
char user[]         = "ESP32";            // MySQL user login username ESP32
char password[]     = "ESP3277";          // MySQL user login password ESP3277
char default_database[] = "ESP32";        // MySQL data base ESP32
char default_table[]    = "PRUEBA2";      // MySQL table PRUEBA
*/

//IPAddress google(172.217.16.142);
IPAddress server_ip;
float retraso = 60000;
unsigned long SEND;
int push = 1;


// Define 

// Sample query
char INSERT_DATA[] = "INSERT INTO %s.%s (Name, Location, Temp1, Temp2, Temp3, Hum1, Hum2, Hum3, Set1, Set2, Set3, REL1, REL2, REL3, REL4, AUX1, AUX2, In1, In2, In3, In4, AL0, AL1, AL2, AL3, AL4, AL5, AL6, AL7, AL8, IP) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')";
                 
char query[512];

/**
 * Instance responsible for implementation of various IOs dependent on EdgeDriver.
 */
extern WebServer  server;
extern AutoConnect portal;
extern WiFiClient    wifiClient;

//WiFiClient    wifiClient;
MySQL_Connection conn((Client *)&wifiClient);


// AutoConnectAux handler. Transfer EdgeData to AutoConnectElement values
String auxSQLCSetting(AutoConnectAux& aux, PageArgument& args) {

  aux["serverNameSQLC"].as<AutoConnectInput>().value = sqlc.data.serverNameSQLC;
  aux["portSQLC"].as<AutoConnectInput>().value = sqlc.data.portSQLC;
  aux["dbnameSQLC"].as<AutoConnectInput>().value = sqlc.data.dbnameSQLC;
  aux["dbtableSQLC"].as<AutoConnectInput>().value = sqlc.data.dbtableSQLC;
  aux["usernameSQLC"].as<AutoConnectInput>().value = sqlc.data.usernameSQLC;
  aux["passwordSQLC"].as<AutoConnectInput>().value = sqlc.data.passwordSQLC;
  aux["sensorLocationSQLC"].as<AutoConnectInput>().value = sqlc.data.sensorLocationSQLC;
  aux["SensorNameSQLC"].as<AutoConnectInput>().value = sqlc.data.SensorNameSQLC;
  aux["timerSQLC"].as<AutoConnectInput>().value = sqlc.data.timerSQLC;
  aux["ValueSQLC"].as<AutoConnectInput>().value = sqlc.data.ValueSQLC;                    // / (30 * 1000);
  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxSQLCStart(AutoConnectAux& aux, PageArgument& args) {

  sqlc.data.serverNameSQLC = aux["serverNameSQLC"].as<AutoConnectText>().value;
  sqlc.data.portSQLC = aux["portSQLC"].as<AutoConnectText>().value;
  sqlc.data.dbnameSQLC = aux["dbnameSQLC"].as<AutoConnectText>().value;
  sqlc.data.dbtableSQLC = aux["dbtableSQLC"].as<AutoConnectText>().value;
  sqlc.data.usernameSQLC = aux["usernameSQLC"].as<AutoConnectText>().value;
  sqlc.data.passwordSQLC = aux["passwordSQLC"].as<AutoConnectText>().value;
  sqlc.data.sensorLocationSQLC = aux["sensorLocationSQLC"].as<AutoConnectText>().value;
  sqlc.data.SensorNameSQLC = aux["SensorNameSQLC"].as<AutoConnectText>().value;
  sqlc.data.timerSQLC = aux["timerSQLC"].as<AutoConnectText>().value;
  sqlc.data.ValueSQLC = aux["ValueSQLC"].as<AutoConnectText>().value;

  sqlc.setEdgeInterval(sqlc.data.timerSQLC.toFloat() *60000L);

  sqlc.save();
  sqlc.start();

  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxSQLCStop(AutoConnectAux& aux, PageArgument& args) {
  sqlc.end();
  aux.redirect("/");
  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxSQLCClear(AutoConnectAux& aux, PageArgument& args) {


  aux.redirect("/");
  return String();
}

// void setup
void startSQLC() {

  Serial.println("Starting SQLC");

  sqlc.setEdgeInterval(sqlc.data.timerSQLC.toFloat() *60000L);

  

}

// void loop
void processSQLC() {


  if (sqlc.data.serverNameSQLC.length()) {

    Serial.println("Starting Process SQLC");

    WiFi.hostByName(sqlc.data.serverNameSQLC.c_str(),server_ip);
    Serial.println(server_ip);


    if (millis() - SEND > retraso) {
    // wifiClient.connect(server_ip, server_port)
    if (!wifiClient.connect(server_ip, sqlc.data.portSQLC.toInt())) {
      Serial.println("SIN INTERNET");
      push = 0;
    }
    else {
      push = 1;
    }   
    SEND = millis();
    }

    if (push == 1){
      INSERT();
      FREE_HEAP();
    } 
  }
}

 
/**
 * SQLC end callback
 */
void endSQLC() {

  sqlc.end();
  Serial.println("SQLC publishing stopped\n");

}


// Serializer: SQLC_t EdgeData. to SQLC EdgeData JSON object. 
void sqlcSerialize(JsonObject& edgeData) {
  edgeData[F("serverNameSQLC")] = sqlc.data.serverNameSQLC;
  edgeData[F("portSQLC")] = sqlc.data.portSQLC;
  edgeData[F("dbnameSQLC")] = sqlc.data.dbnameSQLC;
  edgeData[F("dbtableSQLC")] = sqlc.data.dbtableSQLC;
  edgeData[F("usernameSQLC")] = sqlc.data.usernameSQLC;
  edgeData[F("passwordSQLC")] = sqlc.data.passwordSQLC;
  edgeData[F("sensorLocationSQLC")] = sqlc.data.sensorLocationSQLC;
  edgeData[F("SensorNameSQLC")] = sqlc.data.SensorNameSQLC;
  edgeData[F("timerSQLC")] = sqlc.data.timerSQLC;
  edgeData[F("ValueSQLC")] = sqlc.data.ValueSQLC;
}

// Deserializer: SQLC EdgeData JSON object to SQLC_t EdgeData.
void sqlcDeserialize(JsonObject& edgeData) {
  sqlc.data.serverNameSQLC = edgeData[F("serverNameSQLC")].as<String>();
  sqlc.data.portSQLC = edgeData[F("portSQLC")].as<String>();
  sqlc.data.dbnameSQLC = edgeData[F("dbnameSQLC")].as<String>();
  sqlc.data.dbtableSQLC = edgeData[F("dbtableSQLC")].as<String>();
  sqlc.data.usernameSQLC = edgeData[F("usernameSQLC")].as<String>();
  sqlc.data.passwordSQLC = edgeData[F("passwordSQLC")].as<String>();
  sqlc.data.sensorLocationSQLC = edgeData[F("sensorLocationSQLC")].as<String>();
  sqlc.data.SensorNameSQLC = edgeData[F("SensorNameSQLC")].as<String>();
  sqlc.data.timerSQLC = edgeData[F("timerSQLC")].as<String>();
  sqlc.data.ValueSQLC = edgeData[F("ValueSQLC")].as<String>();

}


void INSERT(){


  //if (conn.connect(server2, server_port, user, password)){
  if (conn.connect(sqlc.data.serverNameSQLC.c_str(), sqlc.data.portSQLC.toInt(), (char*)sqlc.data.usernameSQLC.c_str(), (char*)sqlc.data.passwordSQLC.c_str())){
    

  MySQL_Query query_mem = MySQL_Query(&conn);

  if (conn.connected()) {

    // sprintf(query, INSERT_DATA, data_name, data_table, value, value, value);
    sprintf(query, INSERT_DATA, sqlc.data.dbnameSQLC, sqlc.data.dbtableSQLC,
     sqlc.data.SensorNameSQLC.c_str(),                      //Nombre
     sqlc.data.sensorLocationSQLC.c_str(),                  //Location
     sqlc.data.portSQLC.c_str(),                            //Temp1
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     String(lh_gpio.data.turn_on1),          // RELE1
     String(lh_gpio.data.turn_on2),          // RELE2
     String(lh_gpio.data.turn_on3),          // RELE3
     String(lh_gpio.data.turn_on4),          // RELE4
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     String(lh_gpio.data.status1),               // IN1
     String(lh_gpio.data.status2),               // IN2
     String(lh_gpio.data.status3),               // IN3
     String(lh_gpio.data.status4),               // IN4
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     sqlc.data.ValueSQLC.c_str(),
     WiFi.localIP().toString().c_str());


    if ( !query_mem.execute(query) ) {
      Serial.println("--------------------------------------Complex Insert error");
    }
    else {
      Serial.println("Complex Data Inserted.");
      Serial.println(query);
    }
     
  }
    else {
    Serial.println("Disconnected from Server. Can't insert.");
    }

    conn.close();                     // close the connection
}
    else {
    Serial.println("\nConnect failed. Trying again on next iteration.");
    }

}

