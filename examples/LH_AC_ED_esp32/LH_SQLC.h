/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#ifndef _LH_SQLC_H_
#define _LH_SQLC_H_

#include "EdgeUnified.h"

// Define EdgeData structure for SQLC.
// This is the data structure handled by SQLC EdgeDriver.
typedef struct {
  String  serverNameSQLC;
  String  portSQLC;                  
  String  dbnameSQLC;
  String  dbtableSQLC;
  String  usernameSQLC;
  String  passwordSQLC;
  String  sensorLocationSQLC;
  String  SensorNameSQLC;
  String  timerSQLC = "1";
  String  ValueSQLC;

  String  SQLCAPI;
  String  httpRequestDataSQLC;


  //float SendSQLC;
  //unsigned long publishInterval;
  //unsigned long retryInterval;
  //unsigned long nextPeriod;
  //int   retry;
  //bool  inPublish;
  
} SQLC_t;

// External linkage of EdgeDriver SQLC instance.
extern EdgeDriver<SQLC_t>  sqlc;

// Other required external linkages.
//void startMDNS(void);
void FREE_HEAP(void);

// Declares that main.ino can refer to EdgeDriver's on-demand functions. It is
// referenced by the EdgeUnified::attach function.
void startSQLC(void);
void processSQLC(void);
void endSQLC(void);

void LH_SQLC_LOOP(void);
void INSERT(void);

// When persisting EdgeData containing class objects, a serializer and a
// deserializer are required.
void sqlcSerialize(JsonObject& json);
void sqlcDeserialize(JsonObject& json);

// External linkage of AutoConnectAux JSON definitions.
// These external declarations are referenced by EdgeUnified:join function.
extern const char SETTINGS_SQLC[] PROGMEM;
extern const char START_SQLC[] PROGMEM;
extern const char CLEAR_SQLC[] PROGMEM;
extern const char STOP_SQLC[] PROGMEM;


// AutoConnectAux request handlers
String auxSQLCSetting(AutoConnectAux&, PageArgument&);
String auxSQLCStart(AutoConnectAux&, PageArgument&);
String auxSQLCStop(AutoConnectAux&, PageArgument&);
String auxSQLCClear(AutoConnectAux&, PageArgument&);

#endif // !_LH_SQLC_H_
