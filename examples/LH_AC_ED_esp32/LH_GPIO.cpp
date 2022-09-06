/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#include <Arduino.h>
#include <AutoConnect.h>
#include "EdgeUnified.h"
#include "LH_GPIO.h"


const char SETTINGS_LH_GPIO[] PROGMEM = R"*(
{
  "title": "GPIO Setting",
  "uri": "/lh_gpio",
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
               width: 9em;
               margin: 5px 0 0 0;
               cursor: pointer;
               padding: 5px           
              }

               .noorder input[type='number'] {
               display: inline-block;
               width: 40px;
               height: 25px;
               margin: 5px 0 0 12.5em;
               cursor: pointer;
               padding: 5px;
               text-align: center;
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
        "value": "<h3 style='text-align:center;color:#2f4f4f;margin-top:10px;margin-bottom:10px'>GENERAL PURPOSE IMPUT OUTPUT</h3>"
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
      "name": "IO1",
      "type": "ACInput",
      "label": "BUTTON or IN1:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "5",
      "placeholder": "5",
      "global": true
    },
    {
      "name": "IO2",
      "type": "ACInput",
      "label": "BUTTON or IN2:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "4",
      "placeholder": "4",
      "global": true
    },
    {
      "name": "IO3",
      "type": "ACInput",
      "label": "BUTTON or IN3:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "00",
      "placeholder": "00",
      "global": true
    },
    {
      "name": "IO4",
      "type": "ACInput",
      "label": "BUTTON or IN4:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "2",
      "placeholder": "2",
      "global": true
    },
    {
      "name": "RELE1",
      "type": "ACInput",
      "label": "RELE or OUT1:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "16",
      "placeholder": "16",
      "global": true
    },
    {
      "name": "RELE2",
      "type": "ACInput",
      "label": "RELE or OUT2:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "14",
      "placeholder": "14",
      "global": true
    },
    {
      "name": "RELE3",
      "type": "ACInput",
      "label": "RELE or OUT3:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "12",
      "placeholder": "12",
      "global": true
    },
    {
      "name": "RELE4",
      "type": "ACInput",
      "label": "RELE or OUT4:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "13",
      "placeholder": "13",
      "global": true
    },
    {
      "name": "newline2",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "PROBE1",
      "type": "ACInput",
      "label": "PROBE Sensor 1:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "",
      "placeholder": "",
      "global": true
    },
    {
      "name": "PROBE2",
      "type": "ACInput",
      "label": "PROBE Sensor 2:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "",
      "placeholder": "",
      "global": true
    },
    {
      "name": "PROBE3",
      "type": "ACInput",
      "label": "PROBE Sensor 3:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "",
      "placeholder": "",
      "global": true
    },
    {
      "name": "PROBE4",
      "type": "ACInput",
      "label": "PROBE Sensor 4:",
      "apply": "number",
      "pattern": "\\d*",
      "value": "",
      "placeholder": "",
      "global": true
    },
    {
      "name": "newline3",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "PROBE SETUP",
      "type": "ACSubmit",
      "value": "PROBE SETUP",
      "uri": "/probes_setting"
    },
    {
      "name": "newline4",
      "type": "ACElement",
      "value": "<hr>"
    },
    {
      "name": "BACK",
      "type": "ACSubmit",
      "value": "BACK",
      "uri": "/_ac"
    },
    {
      "name": "SAVE",
      "type": "ACSubmit",
      "value": "SAVE",
      "uri": "/lh_gpio_save"
    }
  ]
}
)*";

const char START_LH_GPIO[] PROGMEM = R"*(
{
  "title": "GPIO SAVED",
  "uri": "/lh_gpio_save",
  "menu": false,
  "element": [

    {
      "name": "IO1",
      "type": "ACText",
      "format": "IO1: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "IO2",
      "type": "ACText",
      "format": "IO1: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "IO3",
      "type": "ACText",
      "format": "IO1: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "IO4",
      "type": "ACText",
      "format": "IO1: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "RELE1",
      "type": "ACText",
      "format": "RELE1: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "RELE2",
      "type": "ACText",
      "format": "RELE2: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "RELE3",
      "type": "ACText",
      "format": "RELE3: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "RELE4",
      "type": "ACText",
      "format": "RELE4: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "PROBE1",
      "type": "ACText",
      "format": "PROBE1: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "PROBE2",
      "type": "ACText",
      "format": "PROBE2: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "PROBE3",
      "type": "ACText",
      "format": "PROBE3: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "PROBE4",
      "type": "ACText",
      "format": "PROBE4: %s",
      "posterior": "br",
      "global": true
    },
    {
      "name": "BACK",
      "type": "ACSubmit",
      "value": "BACK",
      "uri": "/lh_gpio"
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

/**
 * Edge entities
 */
EdgeDriver<LH_GPIO_t>  lh_gpio(start_LH_GPIO, process_LH_GPIO, end_LH_GPIO);

/**
 * AutoConnectAux custom web page request handlers.
 */
// AutoConnectAux handler. Transfer EdgeData to AutoConnectElement values
String aux_LH_GPIOSetting(AutoConnectAux& aux, PageArgument& args) {

  aux["IO1"].as<AutoConnectInput>().value = String(lh_gpio.data.IO1);
  aux["IO2"].as<AutoConnectInput>().value = String(lh_gpio.data.IO2);
  aux["IO3"].as<AutoConnectInput>().value = String(lh_gpio.data.IO3);
  aux["IO4"].as<AutoConnectInput>().value = String(lh_gpio.data.IO4);

  aux["RELE1"].as<AutoConnectInput>().value = String(lh_gpio.data.RELE1);
  aux["RELE2"].as<AutoConnectInput>().value = String(lh_gpio.data.RELE2);
  aux["RELE3"].as<AutoConnectInput>().value = String(lh_gpio.data.RELE3);
  aux["RELE4"].as<AutoConnectInput>().value = String(lh_gpio.data.RELE4);

  aux["PROBE1"].as<AutoConnectInput>().value = String(lh_gpio.data.PROBE1);
  aux["PROBE2"].as<AutoConnectInput>().value = String(lh_gpio.data.PROBE2);
  aux["PROBE3"].as<AutoConnectInput>().value = String(lh_gpio.data.PROBE3);
  aux["PROBE4"].as<AutoConnectInput>().value = String(lh_gpio.data.PROBE4);

  return String();
}

// AutoConnectAux handler. Obtain AutoConnectElement values, copy to EdgeData
String aux_LH_GPIOApply(AutoConnectAux& aux, PageArgument& args) {

  lh_gpio.data.IO1 = aux["IO1"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.IO2 = aux["IO2"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.IO3 = aux["IO3"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.IO4 = aux["IO4"].as<AutoConnectText>().value.toInt();

  lh_gpio.data.RELE1 = aux["RELE1"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.RELE2 = aux["RELE2"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.RELE3 = aux["RELE3"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.RELE4 = aux["RELE4"].as<AutoConnectText>().value.toInt();

  lh_gpio.data.PROBE1 = aux["PROBE1"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.PROBE2 = aux["PROBE2"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.PROBE3 = aux["PROBE3"].as<AutoConnectText>().value.toInt();
  lh_gpio.data.PROBE4 = aux["PROBE4"].as<AutoConnectText>().value.toInt();



  lh_gpio.save();
  lh_gpio.start();


  return String();
}




// void setup
void start_LH_GPIO() {
  Serial.println("Starting LH_GPIO");

  pinMode(lh_gpio.data.IO1, INPUT_PULLUP); 
  pinMode(lh_gpio.data.IO2, INPUT_PULLUP); 
  pinMode(lh_gpio.data.IO3, INPUT_PULLUP); 
  pinMode(lh_gpio.data.IO4, INPUT_PULLUP);

  pinMode(lh_gpio.data.RELE1, OUTPUT);
  digitalWrite(lh_gpio.data.RELE1, LOW);

  pinMode(lh_gpio.data.RELE2, OUTPUT);
  digitalWrite(lh_gpio.data.RELE2, LOW);

  pinMode(lh_gpio.data.RELE3, OUTPUT);
  digitalWrite(lh_gpio.data.RELE3, LOW);

  pinMode(lh_gpio.data.RELE4, OUTPUT);
  digitalWrite(lh_gpio.data.RELE4, LOW);

  pinMode(lh_gpio.data.PROBE1, INPUT_PULLUP); 
  pinMode(lh_gpio.data.PROBE2, INPUT_PULLUP); 
  pinMode(lh_gpio.data.PROBE3, INPUT_PULLUP); 
  pinMode(lh_gpio.data.PROBE4, INPUT_PULLUP);



}

// void loop
void process_LH_GPIO() {

  LH_RELE_STATE();

}


void end_LH_GPIO() {

}




void LH_RELE_STATE(){

  //RELE 1

    lh_gpio.data.status1 = digitalRead(lh_gpio.data.IO1); 
  
    if(lh_gpio.data.status1 && lh_gpio.data.latest1 == 0) 
    {
      lh_gpio.data.turn_on1 = 1 - lh_gpio.data.turn_on1;
      delay(500); 
    }
  
    lh_gpio.data.latest1 = lh_gpio.data.status1; 

    if(lh_gpio.data.turn_on1) 
    {
      digitalWrite(lh_gpio.data.RELE1, LOW); 
      //Serial.println ("RELE1_OFF");
    
    }
  
    else 
    {
      digitalWrite(lh_gpio.data.RELE1, HIGH); 
      //Serial.println ("RELE1_ON");
    
    }  


//RELE 2

    lh_gpio.data.status2 = digitalRead(lh_gpio.data.IO2); 
  
    if(lh_gpio.data.status2 && lh_gpio.data.latest2 == 0) 
    {
      lh_gpio.data.turn_on2 = 1 - lh_gpio.data.turn_on2;
      delay(500); 
    }
  
    lh_gpio.data.latest2 = lh_gpio.data.status2; 
  
    if(lh_gpio.data.turn_on2) 
    {
      digitalWrite(lh_gpio.data.RELE2, LOW); 
      
    
    }
  
    else 
    {
      digitalWrite(lh_gpio.data.RELE2, HIGH); 
      //Serial.println ("RELE2_ON");
    
    }  


//RELE 3

    lh_gpio.data.status3 = digitalRead(lh_gpio.data.IO3); 
  
    if(lh_gpio.data.status3 && lh_gpio.data.latest3 == 0) 
    {
      lh_gpio.data.turn_on3 = 1 - lh_gpio.data.turn_on3;
      delay(500); 
    }
  
    lh_gpio.data.latest3 = lh_gpio.data.status3; 
  
    if(lh_gpio.data.turn_on3) 
    {
      digitalWrite(lh_gpio.data.RELE3, LOW); 
      //Serial.println ("RELE3_OFF");

    }
  
    else 
    {
      digitalWrite(lh_gpio.data.RELE3, HIGH); 
      //Serial.println ("RELE3_ON");
    
    }  


//RELE 4

    lh_gpio.data.status4 = digitalRead(lh_gpio.data.IO4); 
  
    if(lh_gpio.data.status4 && lh_gpio.data.latest4 == 0) 
    {
      lh_gpio.data.turn_on4 = 1 - lh_gpio.data.turn_on4;
      delay(500); 
    }
  
    lh_gpio.data.latest4 = lh_gpio.data.status4; 
  
    if(lh_gpio.data.turn_on4) 
    {
      digitalWrite(lh_gpio.data.RELE4, LOW); 
      //Serial.println ("RELE4_OFF");
      
    }
  
    else 
    {
      digitalWrite(lh_gpio.data.RELE4, HIGH); 
      //Serial.println ("RELE4_ON");

    }  


  }    

