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
 #include "LedBit1.h"
  #define LED1_On()     LedBit1_ClrVal()
    /*!< Turn LED 1 on */
  #define LED1_Off()    LedBit1_SetVal()
    /*!< Turn LED 1 off */
  #define LED1_Neg()    LedBit1_NegVal()
    /*!< Toggle LED 1 */
  #define LED1_Get()    LedBit1_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED1_Put(val) LedBit1_PutVal(val)
    /*!< Turn LED on or off */
  #define LED1_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED1_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#endif

#if PL_NOF_LEDS >= 2
 #include "LedBit2.h"
  #define LED2_On()     LedBit2_ClrVal()
    /*!< Turn LED 1 on */
  #define LED2_Off()    LedBit2_SetVal()
    /*!< Turn LED 1 off */
  #define LED2_Neg()    LedBit2_NegVal()
    /*!< Toggle LED 1 */
  #define LED2_Get()    LedBit2_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED2_Put(val) LedBit2_PutVal(val)
    /*!< Turn LED on or off */
  #define LED2_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED2_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#endif

#if PL_NOF_LEDS >= 3
 #include "LedBit3.h"
  #define LED3_On()     LedBit3_ClrVal()
    /*!< Turn LED 1 on */
  #define LED3_Off()    LedBit3_SetVal()
    /*!< Turn LED 1 off */
  #define LED3_Neg()    LedBit3_NegVal()
    /*!< Toggle LED 1 */
  #define LED3_Get()    LedBit3_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED3_Put(val) LedBit3_PutVal(val)
    /*!< Turn LED on or off */
  #define LED3_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED3_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#endif


void initLED(void);
void testAllLed (void);

void led12On(void);
void led13On(void);
void led23On(void);
void led123On(void);
void led12Off(void);
void led13Off(void);
void led23Off(void);
void led123Off(void);
void testcolour(void);

#endif /* LED_H_ */
