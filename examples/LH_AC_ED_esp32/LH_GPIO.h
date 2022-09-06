/*
  Copyright (c) 2022 Francisco CB (FRANAIRBUS).
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
*/

#ifndef _LH_GPIO_H_
#define _LH_GPIO_H_

#include "EdgeUnified.h"

// Define EdgeData structure for GPIO.
// This is the data structure handled by GPIO EdgeDriver. It has GPIO pins
// connected to LEDs and a blinking cycle.
typedef struct {
  
  //int     pin = LED_BUILTIN;

  int  IO1 = 5;
  int  IO2 = 4;
  int  IO3 = 00;
  int  IO4 = 2;

  int  RELE1 = 16;
  int  RELE2 = 14;
  int  RELE3 = 12;
  int  RELE4 = 13;

  int  PROBE1 = 95;
  int  PROBE2 = 96;
  int  PROBE3 = 97;
  int  PROBE4 = 98;

  int turn_on1 = 0;
  int latest1 = 0;
  int status1 = 0;

  int turn_on2 = 0;
  int latest2 = 0;
  int status2 = 0;

  int turn_on3 = 0;
  int latest3 = 0;
  int status3 = 0;

  int turn_on4 = 0;
  int latest4 = 0;
  int status4 = 0;


} LH_GPIO_t;

// The data members that this structure contains are globally accessible via
// instances of EdgeDriver like as follows:
//    EdgeDriver<GPIO_t>  gpio;
//    gpio.data.pin = 1;
//    unsigned long blink = gpio.data.cycle;
extern EdgeDriver<LH_GPIO_t>  lh_gpio;

// Other required external linkages.
//void startMDNS(void);
void FREE_HEAP(void);

// Declares that main.ino can refer to EdgeDriver's on-demand functions. It is
// referenced by the EdgeUnified::attach function.
void start_LH_GPIO(void);
void process_LH_GPIO(void);
void end_LH_GPIO(void);

void LH_RELE_STATE(void);

// External linkage of AutoConnectAux JSON definitions.
// These external declarations are referenced by EdgeUnified:join function.
extern const char SETTINGS_LH_GPIO[] PROGMEM;
extern const char START_LH_GPIO[] PROGMEM;
//extern const char START_GPIO[] PROGMEM; 

// AutoConnectAux request handlers
String aux_LH_GPIOSetting(AutoConnectAux&, PageArgument&);
String aux_LH_GPIOApply(AutoConnectAux&, PageArgument&);
//String auxGPIOStart(AutoConnectAux&, PageArgument&);

#if defined(ARDUINO_ARCH_ESP8266)
//const uint8_t LED_ACTIVE = LOW;
#elif defined(ARDUINO_ARCH_ESP32)
//const uint8_t LED_ACTIVE = HIGH;
#endif

#endif // !_LH_GPIO_H_ 

