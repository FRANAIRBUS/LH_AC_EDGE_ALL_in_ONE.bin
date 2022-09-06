/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#include <Arduino.h>
#include "LH_PROBES.h"

/**
 * MQTT custom Web page descriptions.
 */
const char SETTINGS_LH_PROBES[] PROGMEM = R"*(
{
  "title": "PROBES Setting",
  "uri": "/probes_setting",
  "menu": false,
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
               width: 200px;
               margin: 5px 0 0 0;
               cursor: pointer;
               padding: 5px           
              }

               .noorder input[type='number'] {
               display: inline-block;
               width: 40px;
               height: 25px;
               margin: 5px 0 0 145px;
               cursor: pointer;
               padding: 5px;
               text-align: center;
               background-color: #EBD7FF 
              }

              .aux-page select {
               display: inline-block;
               width: 150px;
               height: 30px;
               margin: 20px 0 15px 45px;
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
        "value": "<h3 style='text-align:center;color:#2f4f4f;margin-top:10px;margin-bottom:10px'>SELECT PROBE TYPE</h3>"
    },
    {
      "name": "caption",
      "type": "ACText",
      "value": "",
      "style": "text-align:center;font-family:serif;color:#176499;"
    },
    {
      "name": "newline",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "PROBETYPE1",
      "type": "ACSelect",
      "option": [
        "NONE",
        "DS18B20",
        "DHT11",
        "DHT21",
        "DHT22",
        "MQ135",
        "ON-OFF"
      ],
      "label": "PROBE TYPE 2",
      "selected": 4
    },
    {
      "name": "CALT1",
      "type": "ACInput",
      "label": "CALIBRATION PROBE 1 T:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "0",
      "placeholder": "0",
      "global": true
    },
    {
      "name": "CALH1",
      "type": "ACInput",
      "label": "CALIBRATION PROBE 1 H:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "-2",
      "placeholder": "0",
      "global": true
    },
    {
      "name": "newline2",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "PROBETYPE2",
      "type": "ACSelect",
      "option": [
        "NONE",
        "DS18B20",
        "DHT11",
        "DHT21",
        "DHT22",
        "MQ135",
        "ON-OFF"
      ],
      "label": "PROBE TYPE 2",
      "selected": 1
    },
    {
      "name": "CALT2",
      "type": "ACInput",
      "label": "CALIBRATION PROBE 2 T:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "0",
      "placeholder": "0",
      "global": true
    },
    {
      "name": "CALH2",
      "type": "ACInput",
      "label": "CALIBRATION PROBE 2 H:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "-2",
      "placeholder": "0",
      "global": true
    },
    {
      "name": "newline3",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "PROBETYPE3",
      "type": "ACSelect",
      "option": [
        "NONE",
        "DS18B20",
        "MQ135",
        "ON-OFF"
      ],
      "label": "PROBE TYPE 2",
      "selected": 1
    },
    {
      "name": "CALT3",
      "type": "ACInput",
      "label": "CALIBRATION PROBE 3:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "0",
      "placeholder": "0",
      "global": true
    },
    {
      "name": "newline4",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "PROBETYPE4",
      "type": "ACSelect",
      "option": [
        "NONE",
        "DS18B20",
        "MQ135",
        "ON-OFF"
      ],
      "label": "PROBE TYPE 2",
      "selected": 2
    },
    {
      "name": "CALT4",
      "type": "ACInput",
      "label": "CALIBRATION PROBE 4:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "0",
      "placeholder": "0",
      "global": true
    },
    {
      "name": "timerPROBES",
      "type": "ACInput",
      "label": "PROBES Timer Read:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "50",
      "placeholder": "5",
      "global": true
    },
    {
      "name": "newline5",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "BACK",
      "type": "ACSubmit",
      "value": "BACK",
      "uri": "/lh_gpio"
    },
    {
      "name": "save",
      "type": "ACSubmit",
      "value": "Save&amp;Start",
      "uri": "/probes_start"
    }
  ]
}
)*";

const char START_LH_PROBES[] PROGMEM = R"*(
{
    "title": "PROBES Setting",
    "uri": "/probes_start",
    "menu": false,
    "element": [
      {
      "name": "caption",
      "type": "ACText",
      "value": "<h4>Parameters saved as:</h4>",
      "style": "text-align:center;color:#2f4f4f;padding:5px;"
    },
    {
      "name": "PROBETYPE1",
      "type": "ACText",
      "format": "PROBETYPE1: #%s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "CALT1",
      "type": "ACText",
      "format": "CALT1: #%s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "CALH1",
      "type": "ACText",
      "format": "CALH1: #%s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "PROBETYPE2",
      "type": "ACText",
      "format": "PROBETYPE2: #%s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "CALT2",
      "type": "ACText",
      "format": "CALT2: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "CALH2",
      "type": "ACText",
      "format": "CALH2: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "PROBETYPE3",
      "type": "ACText",
      "format": "PROBETYPE3: #%s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "CALT3",
      "type": "ACText",
      "format": "CALT2: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "PROBETYPE4",
      "type": "ACText",
      "format": "PROBETYPE4: #%s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "CALT4",
      "type": "ACText",
      "format": "CALT2: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "timerPROBES",
      "type": "ACText",
      "format": "timer PROBES: %s",
      "posterior": "br",
      "global": true
    },
      {
        "name": "BACK",
        "type": "ACSubmit",
        "value": "BACK",
        "uri": "/probes_setting"
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

const char CLEAR_LH_PROBES[] PROGMEM = R"*(
{
  "title": "PROBES Setting",
  "uri": "/probes_clear",
  "menu": false,
  "response": false
}
)*";

const char STOP_LH_PROBES[] PROGMEM = R"*(
{
  "title": "PROBES Setting",
  "uri": "/probes_stop",
  "menu": false,
  "response": false
}
)*";


EdgeDriver<PROBES_t>  probes(start_LH_PROBES, process_LH_PROBES, end_LH_PROBES);

extern WebServer  server;
extern AutoConnect portal;


String aux_LH_PROBES_Setting(AutoConnectAux& aux, PageArgument& args) {

  aux["PROBETYPE1"].as<AutoConnectSelect>().selected = probes.data.PROBETYPE1.toInt(); 
  aux["CALT1"].as<AutoConnectInput>().value = probes.data.CALT1;
  aux["CALH1"].as<AutoConnectInput>().value = probes.data.CALH1;

  aux["PROBETYPE2"].as<AutoConnectSelect>().selected = probes.data.PROBETYPE2.toInt();
  aux["CALT2"].as<AutoConnectInput>().value = probes.data.CALT2;
  aux["CALH2"].as<AutoConnectInput>().value = probes.data.CALH2;

  aux["PROBETYPE3"].as<AutoConnectSelect>().selected = probes.data.PROBETYPE3.toInt();
  aux["CALT3"].as<AutoConnectInput>().value = probes.data.CALT3;

  aux["PROBETYPE4"].as<AutoConnectSelect>().selected = probes.data.PROBETYPE4.toInt();
  aux["CALT4"].as<AutoConnectInput>().value = probes.data.CALT4;

  aux["timerPROBES"].as<AutoConnectInput>().value = probes.data.timerPROBES;    

  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String aux_LH_PROBES_Start(AutoConnectAux& aux, PageArgument& args) {

  const AutoConnectAux* requestAux = portal.aux(portal.where());

  probes.data.PROBETYPE1 = ((AutoConnectAux&)(*requestAux))["PROBETYPE1"].as<AutoConnectSelect>().selected;
  probes.data.CALT1 = aux["CALT1"].as<AutoConnectText>().value;
  probes.data.CALH1 = aux["CALH1"].as<AutoConnectText>().value;

  probes.data.PROBETYPE2 = ((AutoConnectAux&)(*requestAux))["PROBETYPE2"].as<AutoConnectSelect>().selected;
  probes.data.CALT2 = aux["CALT2"].as<AutoConnectText>().value;
  probes.data.CALH2 = aux["CALH2"].as<AutoConnectText>().value;

  probes.data.PROBETYPE3 = ((AutoConnectAux&)(*requestAux))["PROBETYPE3"].as<AutoConnectSelect>().selected;
  probes.data.CALT3 = aux["CALT3"].as<AutoConnectText>().value;

  probes.data.PROBETYPE4 = ((AutoConnectAux&)(*requestAux))["PROBETYPE4"].as<AutoConnectSelect>().selected; //value()
  probes.data.CALT4 = aux["CALT4"].as<AutoConnectText>().value;

  probes.data.timerPROBES = aux["timerPROBES"].as<AutoConnectText>().value;

  probes.setEdgeInterval(probes.data.timerPROBES.toFloat() *1000L);

  probes.save();
  probes.start();

  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String aux_LH_PROBES_Stop(AutoConnectAux& aux, PageArgument& args) {
  probes.end();
  aux.redirect("/");
  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String aux_LH_PROBES_Clear(AutoConnectAux& aux, PageArgument& args) {

  aux.redirect("/");
  return String();
}


// void setup
void start_LH_PROBES() {

  probes.setEdgeInterval(probes.data.timerPROBES.toFloat() *1000L);

  
}

// void loop
void process_LH_PROBES() {

    Serial.println("Starting Process PROBES");

    Serial.print("PROBETYPE1: ");
    Serial.println(probes.data.PROBETYPE1);
    //Serial.print("PROBETYPE2: ");
    //Serial.println(probes.data.PROBETYPE2);
    //Serial.print("PROBETYPE3: ");
    //Serial.println(probes.data.PROBETYPE3);
    //Serial.print("PROBETYPE4: ");
    //Serial.println(probes.data.PROBETYPE4);

   // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (3.5 / 1023.0);
  // print out the value you read:
  Serial.print(voltage);
  Serial.println(" voltage A0");

  FREE_HEAP();

}

 
void end_LH_PROBES() {
 
  Serial.println("EDGE MENU stopped\n");

}
