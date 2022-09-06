/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#ifndef _LH_PROBES_H_
#define _LH_PROBES_H_

#include "EdgeUnified.h"

// Define EdgeData structure for MENU.
// This is the data structure handled by MENU EdgeDriver.
typedef struct {

  String  PROBETYPE1;
  String  CALT1;
  String  CALH1;
  //int  n_PROBETYPE2;
  String  PROBETYPE2;
  String  CALT2;
  String  CALH2;
  //int  n_PROBETYPE3;
  String  PROBETYPE3;
  String  CALT3;
  //int  n_PROBETYPE4;
  String  PROBETYPE4;
  String  CALT4;

  String timerPROBES = "30";

  


  
  
} PROBES_t;

// External linkage of EdgeDriver MENU instance.
extern EdgeDriver<PROBES_t>  probes;

// Other required external linkages.
//void startMDNS(void);
void FREE_HEAP(void);

// Declares that main.ino can refer to EdgeDriver's on-demand functions. It is
// referenced by the EdgeUnified::attach function.
void start_LH_PROBES(void);
void process_LH_PROBES(void);
void end_LH_PROBES(void);



// When persisting EdgeData containing class objects, a serializer and a
// deserializer are required.
//void PROBESSerialize(JsonObject& json);
//void PROBESDeserialize(JsonObject& json);

// External linkage of AutoConnectAux JSON definitions.
// These external declarations are referenced by EdgeUnified:join function.
extern const char SETTINGS_LH_PROBES[] PROGMEM;
extern const char START_LH_PROBES[] PROGMEM;
extern const char CLEAR_LH_PROBES[] PROGMEM;
extern const char STOP_LH_PROBES[] PROGMEM;


// AutoConnectAux request handlers
String aux_LH_PROBES_Setting(AutoConnectAux&, PageArgument&);
String aux_LH_PROBES_Start(AutoConnectAux&, PageArgument&);
String aux_LH_PROBES_Stop(AutoConnectAux&, PageArgument&);
String aux_LH_PROBES_Clear(AutoConnectAux&, PageArgument&);


#endif // !_LH_PROBES_H_