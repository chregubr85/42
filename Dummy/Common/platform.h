/**
 * This is the platform configuration file.
 * @author: Stefan Portmann
 * @date: 25.09.2014
 * @version: 0.1
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"
#include "PE_Error.h"
#include "stddef.h"


#define PL_IS_FRDM (defined(PL_BOARD_IS_FRDM))
#define PL_IS_ROBO (defined(PL_BOARD_IS_ROBO))


#if  PL_IS_FRDM
	#define PL_NOF_LEDS 3
		//FRDM board has 3 LEDs(RGB)

  	  #define LedRED_On() 		LED1_On()
  	  #define LedRED_Off() 		LED1_Off()
  	  #define LedRED_Neg()		LED1_Neg()
  	  #define LedRED_Get() 		LED1_Get()
  	  #define LedRED_Put(val) 	LED1_Put(val)
  	  #define LedRED_Init() 	LED1_Init()
  	  #define LedRED_Deinit() 	LED1_Deinit()


  	  #define LedGREEN_On() 	LED2_On()
  	  #define LedGREEN_Off() 	LED2_Off()
  	  #define LedGREEN_Neg()	LED2_Neg()
  	  #define LedGREEN_Get() 	LED2_Get()
  	  #define LedGREEN_Put(val) LED2_Put(val)
  	  #define LedGREEN_Init() 	LED2_Init()
  	  #define LedGREEN_Deinit() LED2_Deinit()


  	  #define LedBLUE_On() 		LED3_On()
  	  #define LedBLUE_Off() 	LED3_Off()
  	  #define LedBLUE_Neg()		LED3_Neg()
  	  #define LedBLUE_Get() 	LED3_Get()
  	  #define LedBLUE_Put(val) 	LED3_Put(val)
  	  #define LedBLUE_Init() 	LED3_Init()
  	  #define LedBLUE_Deinit() 	LED3_Deinit()

	  #define LedYELLOW_On()		led12On()
	  #define LedVIOLET_On()		led13On()
	  #define LedTORQUOISE_On()		led23On()
	  #define LedWHITE_On()			led123On()
	  #define LedYELLOW_Off()		led12Off()
	  #define LedVIOLET_Off()		led13Off()
	  #define LedTORQUOISE_Off()	led23Off()
	  #define LedWHITE_Off()		led123Off()

	  #define PL_HAS_EVENTS 1
		// FRDM Board supports Events
	  #define PL_HAS_TIMER 1


#elif PL_IS_ROBO
	#define PL_NOF_LEDS 2
		//robo has 2 LEDs
#else
	#error "unknown board?"
#endif



#endif	/*PLATFORM_H_*/
