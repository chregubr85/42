/*
 * LED.h
 *
 *  Created on: 26.09.2014
 *      Author: Daniel Keusch
 */

#ifndef LED_H_
#define LED_H_


#include "platform.h"

#if PL_NOF_LEDS >= 1
  #include "LEDblue.h"
  #define LEDBLUE_On()     LedBit1_ClrVal()
    /*!< Turn LED 1 on */
  #define LEDBLUE_Off()    LedBit1_SetVal()
    /*!< Turn LED 1 off */
  #define LEDBLUE_Neg()    LedBit1_NegVal()
    /*!< Toggle LED 1 */
  #define LEDBLUE_Get()    LedBit1_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LEDBLUE_Put(val) LedBit1_PutVal(val)
    /*!< Turn LED on or off */
  #define LEDBLUE_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LEDBLUE_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#else
  #define LEDBLUE_On()     /* do nothing */
    /*!< Turn LED 1 on */
  #define LEDBLUE_Off()    /* do nothing */
    /*!< Turn LED 1 off */
  #define LEDBLUE_Neg()    /* do nothing */
    /*!< Toggle LED 1 */
  #define LEDBLUE_Get()  0 /* do nothing */
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LEDBLUE_Put(val) /* do nothing */
    /*!< Turn LED 1 on or off */
  #define LEDBLUE_Init()   /* do nothing */
    /*!< Initialize LED 1 */
  #define LEDBLUE_Deinit() /* do nothing */
    /*!< De-Initialize LED 1 */
#endif

#endif /* LED_H_ */
