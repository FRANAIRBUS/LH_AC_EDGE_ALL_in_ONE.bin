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
//#include <PubSubClient.h>
#include "EdgeUnified.h"
#include "LH_MySQL.h"

#include "LH_GPIO.h"

/**
 * MQTT custom Web page descriptions.
 */
const char SETTINGS_MySQL[] PROGMEM = R"*(
{
  "title": "MySQL Setting",
  "uri": "/mysql_setting",
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
        "value": "<h3 style='text-align:center;color:#2f4f4f;margin-top:10px;margin-bottom:10px'>SERVER MySQL SETTINGS</h3>"
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
      "name": "serverNameMySQL",
      "type": "ACInput",
      "label": "Server:",
      "pattern": "http://iot.imofrio.es/posti.php",
      "value": "",
      "placeholder": "http://server.com:3306",
      "global": true
    },
    {
      "name": "apiKeyMySQL",
      "type": "ACInput",
      "label": "Api Key:",
      "pattern": "",
      "value": "tPmAT5Ab3j7F9",
      "placeholder": "optional",
      "global": true
    },
    {
      "name": "dbnameMySQL",
      "type": "ACInput",
      "label": "Name Table:",
      "pattern": "",
      "value": "",
      "placeholder": "required",
      "global": true
    },
    {
      "name": "usernameMySQL",
      "type": "ACInput",
      "label": "User Name:",
      "pattern": "",
      "value": "imofrio_iot",
      "placeholder": "required",
      "global": true
    },
    {
      "name": "passwordMySQL",
      "type": "ACInput",
      "label": "Password:",
      "pattern": "",
      "value": "IMOFRIO202011111111111",
      "placeholder": "required",
      "global": true
    },
    {
      "name": "sensorLocation",
      "type": "ACInput",
      "label": "Sys Location:",
      "pattern": "",
      "value": "",
      "placeholder": "optional",
      "global": true
    },
    {
      "name": "SensorName",
      "type": "ACInput",
      "label": "System Name:",
      "pattern": "",
      "value": "",
      "placeholder": "optional",
      "global": true
    },
    {
      "name": "timerMySQL",
      "type": "ACInput",
      "label": "Timer Send:",
      "pattern": "",
      "value": "0.5",
      "placeholder": "minute",
      "global": true
    },
    {
      "name": "Value",
      "type": "ACInput",
      "label": "Value",
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
      "uri": "/mysql_stop"
    },
    {
      "name": "save",
      "type": "ACSubmit",
      "value": "Save&amp;Start",
      "uri": "/mysql_start"
    }
  ]
}
)*";

const char START_MySQL[] PROGMEM = R"*(
{
  "title": "MySQL Setting",
  "uri": "/mysql_start",
  "menu": false,
  "element": [
    {
      "name": "caption",
      "type": "ACText",
      "value": "<h4>Parameters saved as:</h4>",
      "style": "text-align:center;color:#2f4f4f;padding:5px;"
    },
    {
      "name": "serverNameMySQL",
      "type": "ACText",
      "format": "server MySQL: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "apiKeyMySQL",
      "type": "ACText",
      "format": "api Key MySQL: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "dbnameMySQL",
      "type": "ACText",
      "format": "dbname MySQL: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "usernameMySQL",
      "type": "ACText",
      "format": "username MySQL: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "passwordMySQL",
      "type": "ACText",
      "format": "password MySQL: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "sensorLocation",
      "type": "ACText",
      "format": "sensor Location: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "SensorName",
      "type": "ACText",
      "format": "Sensor Name: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "timerMySQL",
      "type": "ACText",
      "format": "timer MySQL: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "Value",
      "type": "ACText",
      "format": "Value: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "BACK",
      "type": "ACSubmit",
      "value": "BACK",
      "uri": "/mysql_setting"
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

const char CLEAR_MySQL[] PROGMEM = R"*(
{
  "title": "MySQL Setting",
  "uri": "/mysql_clear",
  "menu": false,
  "response": false
}
)*";

const char STOP_MySQL[] PROGMEM = R"*(
{
  "title": "MySQL Setting",
  "uri": "/mysql_stop",
  "menu": false,
  "response": false
}
)*";

/**
 * Edge entities
 */
EdgeDriver<MySQL_t>  mysql(startMySQL, processMySQL, endMySQL);

/**
 * Instance responsible for implementation of various IOs dependent on EdgeDriver.
 */
extern WebServer  server;
extern AutoConnect portal;
extern WiFiClient    wifiClient;
//PubSubClient  mqttClient(wifiClient);


// AutoConnectAux handler. Transfer EdgeData to AutoConnectElement values
String auxMySQLSetting(AutoConnectAux& aux, PageArgument& args) {

  aux["serverNameMySQL"].as<AutoConnectInput>().value = mysql.data.serverNameMySQL;
  aux["apiKeyMySQL"].as<AutoConnectInput>().value = mysql.data.apiKeyMySQL;
  aux["dbnameMySQL"].as<AutoConnectInput>().value = mysql.data.dbnameMySQL;
  aux["usernameMySQL"].as<AutoConnectInput>().value = mysql.data.usernameMySQL;
  aux["passwordMySQL"].as<AutoConnectInput>().value = mysql.data.passwordMySQL;
  aux["sensorLocation"].as<AutoConnectInput>().value = mysql.data.sensorLocation;
  aux["SensorName"].as<AutoConnectInput>().value = mysql.data.SensorName;
  aux["timerMySQL"].as<AutoConnectInput>().value = mysql.data.timerMySQL;
  aux["Value"].as<AutoConnectInput>().value = mysql.data.Value;                    // / (30 * 1000);
  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxMySQLStart(AutoConnectAux& aux, PageArgument& args) {

  mysql.data.serverNameMySQL = aux["serverNameMySQL"].as<AutoConnectText>().value;
  mysql.data.apiKeyMySQL = aux["apiKeyMySQL"].as<AutoConnectText>().value;
  mysql.data.dbnameMySQL = aux["dbnameMySQL"].as<AutoConnectText>().value;
  mysql.data.usernameMySQL = aux["usernameMySQL"].as<AutoConnectText>().value;
  mysql.data.passwordMySQL = aux["passwordMySQL"].as<AutoConnectText>().value;
  mysql.data.sensorLocation = aux["sensorLocation"].as<AutoConnectText>().value;
  mysql.data.SensorName = aux["SensorName"].as<AutoConnectText>().value;
  mysql.data.timerMySQL = aux["timerMySQL"].as<AutoConnectText>().value;
  mysql.data.Value = aux["Value"].as<AutoConnectText>().value;

  mysql.setEdgeInterval(mysql.data.timerMySQL.toFloat() *60000L);

  mysql.save();
  mysql.start();

  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxMySQLStop(AutoConnectAux& aux, PageArgument& args) {
  mysql.end();
  aux.redirect("/");
  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String auxMySQLClear(AutoConnectAux& aux, PageArgument& args) {
  //HTTPClient  http;

  aux.redirect("/");
  return String();
}

// void setup
void startMySQL() {

  Serial.println("Starting MySQL");
  mysql.setEdgeInterval(mysql.data.timerMySQL.toFloat() *60000L);
  
}

// void loop
void processMySQL() {

  IPAddress server_addr(10,0,1,35);

  if (mysql.data.serverNameMySQL.length()) {

    Serial.println("Starting Process MySQL");

    WiFi.hostByName(mysql.data.serverNameMySQL.c_str(),server_addr);

    Serial.println("connect to server ip: " + server_addr);

    LH_MySQL_LOOP();

    FREE_HEAP();

  }
}

 

// MySQL end callback
void endMySQL() {
  
  mysql.end();
  Serial.println("MySQL publishing stopped\n");

}

// Serializer: MySQL_t EdgeData. to MySQL EdgeData JSON object. 
void mysqlSerialize(JsonObject& edgeData) {
  edgeData[F("serverNameMySQL")] = mysql.data.serverNameMySQL;
  edgeData[F("apiKeyMySQL")] = mysql.data.apiKeyMySQL;
  edgeData[F("dbnameMySQL")] = mysql.data.dbnameMySQL;
  edgeData[F("usernameMySQL")] = mysql.data.usernameMySQL;
  edgeData[F("passwordMySQL")] = mysql.data.passwordMySQL;
  edgeData[F("sensorLocation")] = mysql.data.sensorLocation;
  edgeData[F("SensorName")] = mysql.data.SensorName;
  edgeData[F("timerMySQL")] = mysql.data.timerMySQL;
  edgeData[F("Value")] = mysql.data.Value;
}

// Deserializer: MySQL EdgeData JSON object to MySQL_t EdgeData.
void mysqlDeserialize(JsonObject& edgeData) {
  mysql.data.serverNameMySQL = edgeData[F("serverNameMySQL")].as<String>();
  mysql.data.apiKeyMySQL = edgeData[F("apiKeyMySQL")].as<String>();
  mysql.data.dbnameMySQL = edgeData[F("dbnameMySQL")].as<String>();
  mysql.data.usernameMySQL = edgeData[F("usernameMySQL")].as<String>();
  mysql.data.passwordMySQL = edgeData[F("passwordMySQL")].as<String>();
  mysql.data.sensorLocation = edgeData[F("sensorLocation")].as<String>();
  mysql.data.SensorName = edgeData[F("SensorName")].as<String>();
  mysql.data.timerMySQL = edgeData[F("timerMySQL")].as<String>();
  mysql.data.Value = edgeData[F("Value")].as<String>();

}


void LH_MySQL_LOOP(){


  HTTPClient http;

  if (http.begin(wifiClient, mysql.data.serverNameMySQL)) {  


    int httpCode = http.GET();
        if(httpCode > 0) {

          Serial.printf("[HTTP] GET ...Response code: %d\n", httpCode);
          
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

          String MySQLAPI  =      
                              "api_key=" + mysql.data.apiKeyMySQL
                            + "&DB_name=" + mysql.data.dbnameMySQL 
                            + "&DB_user=" + mysql.data.usernameMySQL 
                            + "&DB_pass=" + mysql.data.passwordMySQL;


          String httpRequestData = 

                            "&Nombre=" + String(mysql.data.SensorName) 
                            + "&Lugar=" + String(mysql.data.sensorLocation) 
                            + "&Temp1=" + String(mysql.data.Value)
                            + "&Temp2=" + String(mysql.data.Value) 
                            + "&Temp3=" + String(mysql.data.Value) 
                            + "&Hum1=" + String(mysql.data.Value) 
                            + "&Hum2=" + String(mysql.data.Value) 
                            + "&Hum3=" + String(mysql.data.Value) 
                            + "&Set1=" + String(mysql.data.Value) 
                            + "&Set2=" + String(mysql.data.Value) 
                            + "&Set3=" + String(mysql.data.Value) 
                            + "&REL1=" + String(lh_gpio.data.turn_on1) 
                            + "&REL2=" + String(lh_gpio.data.turn_on2) 
                            + "&REL3=" + String(lh_gpio.data.turn_on3)
                            + "&REL4=" + String(lh_gpio.data.turn_on4)
                            + "&AUX1=" + String(mysql.data.Value) 
                            + "&AUX2=" + String(mysql.data.Value)
                            + "&In1=" + String(lh_gpio.data.IO1) 
                            + "&In2=" + String(lh_gpio.data.IO2)
                            + "&In3=" + String(lh_gpio.data.IO3) 
                            + "&In4=" + String(lh_gpio.data.IO4)
                            + "&AL0=" + String(mysql.data.Value) 
                            + "&AL1=" + String(mysql.data.Value)
                            + "&AL2=" + String(mysql.data.Value) 
                            + "&AL3=" + String(mysql.data.Value)
                            + "&AL4=" + String(mysql.data.Value) 
                            + "&AL5=" + String(mysql.data.Value)
                            + "&AL6=" + String(mysql.data.Value) 
                            + "&AL7=" + String(mysql.data.Value)
                            + "&AL8=" + String(mysql.data.Value) 
                            + "&IP=" + (WiFi.localIP().toString()) 
                            + "";

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");     // Specify content-type header
  int httpResponseCode = http.POST(MySQLAPI + httpRequestData);     // Send HTTP POST request

  if (httpResponseCode == 200) {
    Serial.println(MySQLAPI + httpRequestData);
    Serial.println("httpRequestData servidor 1 OK: MySQL DATA SEND:");   
  }
  
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

       }  
  }
   
  else {
    Serial.println("Error MySQL server NO connected: ");
    Serial.printf("[HTTP] GET ...Response code: %d\n", httpCode);
    Serial.println("");
  }
  }

}
