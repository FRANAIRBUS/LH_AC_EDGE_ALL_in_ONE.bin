/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#ifndef _LH_MENU_H_
#define _LH_MENU_H_

#include "EdgeUnified.h"

// Define EdgeData structure for MENU.
// This is the data structure handled by MENU EdgeDriver.
typedef struct {
  bool Use_MySQL;
  bool Use_HOMEKIT;
  bool Use_MQTT;
  bool Use_BUILTIN;
  bool Use_SQLC;

  String LH_HOSTNAME;
  String COMAND;

  
  
} MENU_t;

// External linkage of EdgeDriver MENU instance.
extern EdgeDriver<MENU_t>  menu;

// Other required external linkages.
//void startMDNS(void);
void FREE_HEAP(void);

void startMDNS(void);

// Declares that main.ino can refer to EdgeDriver's on-demand functions. It is
// referenced by the EdgeUnified::attach function.
void startMENU(void);
void processMENU(void);
void endMENU(void);

void LH_MENU_LOOP(void);

// When persisting EdgeData containing class objects, a serializer and a
// deserializer are required.
void menuSerialize(JsonObject& json);
void menuDeserialize(JsonObject& json);

// External linkage of AutoConnectAux JSON definitions.
// These external declarations are referenced by EdgeUnified:join function.
extern const char SETTINGS_MENU[] PROGMEM;
extern const char START_MENU[] PROGMEM;
extern const char CLEAR_MENU[] PROGMEM;
extern const char STOP_MENU[] PROGMEM;


// AutoConnectAux request handlers
String auxMENUSetting(AutoConnectAux&, PageArgument&);
String auxMENUStart(AutoConnectAux&, PageArgument&);
String auxMENUStop(AutoConnectAux&, PageArgument&);
String auxMENUClear(AutoConnectAux&, PageArgument&);


#endif // !_LH_MENU_H_