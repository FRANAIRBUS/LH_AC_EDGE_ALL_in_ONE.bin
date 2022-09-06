/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#ifndef _LH_MySQL_H_
#define _LH_MySQL_H_

#include "EdgeUnified.h"

// Define EdgeData structure for MySQL.
// This is the data structure handled by MySQL EdgeDriver.
typedef struct {
  String  serverNameMySQL;
  String  apiKeyMySQL;                  
  String  dbnameMySQL;
  String  usernameMySQL;
  String  passwordMySQL;
  String  sensorLocation;
  String  SensorName;
  String  timerMySQL = "1";
  String  Value;

  String  MySQLAPI;
  String  httpRequestData;

  //float SendMySQL;
  //unsigned long publishInterval;
  //unsigned long retryInterval;
  //unsigned long nextPeriod;
  //int   retry;
  //bool  inPublish;
  
} MySQL_t;

// External linkage of EdgeDriver MySQL instance.
extern EdgeDriver<MySQL_t>  mysql;

// Other required external linkages.
//void startMDNS(void);
void FREE_HEAP(void);

// Declares that main.ino can refer to EdgeDriver's on-demand functions. It is
// referenced by the EdgeUnified::attach function.
void startMySQL(void);
void processMySQL(void);
void endMySQL(void);

void LH_MySQL_LOOP(void);

// When persisting EdgeData containing class objects, a serializer and a
// deserializer are required.
void mysqlSerialize(JsonObject& json);
void mysqlDeserialize(JsonObject& json);

// External linkage of AutoConnectAux JSON definitions.
// These external declarations are referenced by EdgeUnified:join function.
extern const char SETTINGS_MySQL[] PROGMEM;
extern const char START_MySQL[] PROGMEM;
extern const char CLEAR_MySQL[] PROGMEM;
extern const char STOP_MySQL[] PROGMEM;


// AutoConnectAux request handlers
String auxMySQLSetting(AutoConnectAux&, PageArgument&);
String auxMySQLStart(AutoConnectAux&, PageArgument&);
String auxMySQLStop(AutoConnectAux&, PageArgument&);
String auxMySQLClear(AutoConnectAux&, PageArgument&);

#endif // !_LH_MySQL_H_
