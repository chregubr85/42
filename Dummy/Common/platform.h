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

#define PL_BOARD_IS_FRDM (defined(PL_BOARD_IS_FRDM))
#define PL_BOARD_IS_ROBO (defined(PL_BOARD_IS_ROBO))


#if PL_BOARD_IS_FRDM
	#define PL_NOF_LEDS 3
		//FRDM board has 3 LEDs(RGB)
	#define LED_RED LED_1
	#define LED_BLUE LED_2
	#define LED_GREEN LED_3

#elif PL_BOARD_IS_ROBO
	#define PL_NOF_LEDS 2
		//robo has 2 LEDs
#else
	#error "unknown board?"
#endif


#endif	/*PLATFORM_H_*/
