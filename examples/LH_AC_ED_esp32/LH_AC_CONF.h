/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#ifndef _LH_AC_CONF_H_
#define _LH_AC_CONF_H_


#include "LH_MENU.h"
#include "MyMqtt.h"


/*
void handleRoot() {
  String  content =
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "</head>"
    "<body>"
    "<p style=\"padding-top:10px;text-align:center\"> <IMG SRC='https://lh3.googleusercontent.com/rqwB8axgzo89sgatVqJNDA5YHoquIp6DaJxkmSEoHBzwiVMa3BMfG5EYby2t0DYcB6xDd7SlE5BYlU5CNbs91Xoiib1S66uwrYb5yw' style='max-width:100%;width:auto;height:auto;'> </p>"
    "<p style=\"padding-top:10px;text-align:center\"> <a href='https://www.google.com/'>www.google.com</a> </p>"
    "<p style=\"padding-top:10px;text-align:center\"> <a href='/_ac'>CONFIGURATION</a> </p>"      
    "</body>"
    "</html>";

  server.send(200, "text/html", content);
}

*/

void handleRoot() {
  String  content =
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "</head>"
    "<body>"
    "<iframe width=\"450\" height=\"260\" style=\"transform:scale(0.79);-o-transform:scale(0.79);-webkit-transform:scale(0.79);-moz-transform:scale(0.79);-ms-transform:scale(0.79);transform-origin:0 0;-o-transform-origin:0 0;-webkit-transform-origin:0 0;-moz-transform-origin:0 0;-ms-transform-origin:0 0;border: 1px solid #cccccc;\" src=\"https://thingspeak.com/channels/{{CHANNEL}}/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&type=line\"></iframe>"
    "<p style=\"padding-top:5px;text-align:center\">" AUTOCONNECT_LINK(COG_24) "</p>"
    "</body>"
    "</html>";

  content.replace("{{CHANNEL}}", mqtt.data.channelid);
  server.send(200, "text/html", content);
}



void startMDNS(void) {
  if (MDNS.queryService("http", "tcp"))
    MDNS.end();

  String tcpName = "LH-" + menu.data.LH_HOSTNAME;
  const char* LH_HOSTNAME = WiFi.getHostname();
 
  if (menu.data.LH_HOSTNAME.length()) { 
    LH_HOSTNAME = tcpName.c_str();
  }  

  Serial.printf("mDNS responder %s.local start", LH_HOSTNAME);
  if (MDNS.begin(LH_HOSTNAME)) {
    MDNS.addService("http", "tcp", 80);
    Serial.println("ed");
  }
  else {
    Serial.println(" failed");
  }
}

void onWiFiConnect(IPAddress& ip) {
  Serial.println("connected:" + WiFi.SSID());
  Serial.println("IP:" + WiFi.localIP().toString());
  startMDNS();
}

/*
const uint16_t  CREDENTIAL_OFFSET = 2048;
const char* CREDENTIAL_DIR = "/";
const char* CREDENTIAL_FILEPREFIX = "ac_";

bool restoreCredentials(const uint16_t offset, const char* dir, const char* prefix) {
  if (!LittleFS.begin()) {
    Serial.println("Fails LittleFS start");
    return false;
  }

  Dir root = LittleFS.openDir(dir);
  while (root.next()) {
    if (root.fileName().startsWith(prefix)) {
      File  file = root.openFile("r");
      if (file) {
        AutoConnectCredential credt(offset);
        station_config_t  sta_config;
        if (file.readBytes((char*)&sta_config, sizeof(sta_config))) {
          if (credt.save(&sta_config))
            Serial.printf("Credential:%s restored\n", (char*)sta_config.ssid);
          else
            Serial.printf("Failed to restore credential %s\n", (char*)sta_config.ssid);
        }
        else
          Serial.printf("Failed to load credential %s\n", file.name());
        file.close();
      }
    }
  }

  LittleFS.end();
  return true;
}

bool saveCredentials(const uint16_t offset, const char* dir, const char* prefix) {
  if (!LittleFS.begin()) {
    Serial.println("Fails LittleFS start");
    return false;
  }

  AutoConnectCredential credt(offset);
  station_config_t  sta_config;

  bool  rc = true;
  uint8_t entries = credt.entries();
  Serial.printf("%" PRIu8 " available credential(s)\n", entries);
  for (uint8_t i = 0; i < entries; i++) {
    credt.load(i, &sta_config);
    Serial.printf("Credential(%" PRIu8 ") %s, ", i, (char*)sta_config.ssid);
    String  cfName = String(dir) + String(prefix) + String((char*)sta_config.ssid);
    File  credential = LittleFS.open(cfName, "w");
    if (credential.write((uint8_t*)&sta_config, sizeof(station_config_t)))
      Serial.printf("saved to %s\n", cfName.c_str());
    else {
      Serial.println("failed to save");
      rc = false;
    }
    credential.close();
  }

  return rc;
}

*/

void LH_AC_SETUP() {

  config.title = "LH HOME SOFT";

  //restoreCredentials(CREDENTIAL_OFFSET, CREDENTIAL_DIR, CREDENTIAL_FILEPREFIX);

  server.on("/", handleRoot);

  config.homeUri = "/";
  config.bootUri = AC_ONBOOTURI_HOME;

  Serial.println("AP INITIAL ID: " + config.apid);
 
  if (menu.data.LH_HOSTNAME.length()) { 
    config.apid = menu.data.LH_HOSTNAME + "-LH-" + String(GET_CHIPID(), HEX) ;
    Serial.println("AP USER ID: " + config.apid);
  }  

  else {
    config.apid = "LH-" + String(GET_CHIPID(), HEX);
    Serial.println("AP LH ID: " + config.apid);
  } 
    Serial.println("Connect with AP to configure: " + config.apid);

  
  config.staip = IPAddress(192,168,20,0);
  config.staGateway = IPAddress(192,168,20,1);
  config.staNetmask = IPAddress(255,255,255,0); 
  config.dns1 = IPAddress(8,8,8,8);        
  config.dns2 = IPAddress(8,8,4,4);  


  config.auth = AC_AUTH_BASIC;
  config.authScope = AC_AUTHSCOPE_AUX; // | AC_AUTHSCOPE_WITHCP;
  config.username = USERNAME;
  config.password = PASSWORD;      



  config.portalTimeout = 3000; 
  config.autoReconnect = true;  // Reconnect to known access points.
  config.reconnectInterval = 2; // Reconnection attempting interval is 30 seg.
  config.retainPortal = true;   // Keep the captive portal open.
  //config.autoRise = false;

  config.menuItems = AC_MENUITEM_CONFIGNEW | AC_MENUITEM_OPENSSIDS | AC_MENUITEM_DISCONNECT | AC_MENUITEM_RESET | AC_MENUITEM_UPDATE |AC_MENUITEM_DELETESSID;
      
  //config.boundaryOffset = CREDENTIAL_OFFSET;
  config.ota = AC_OTA_BUILTIN;   // OTA

  portal.config(config);

  portal.onConnect(onWiFiConnect);

#if defined(ARDUINO_ARCH_ESP8266)
  LittleFS.begin();
#elif defined(ARDUINO_ARCH_ESP32)
  SPIFFS.begin(true);
#endif


}


#endif // !_LH_AC_CONF_H_