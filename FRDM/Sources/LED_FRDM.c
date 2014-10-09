/*
 * LED_FRDM.c
 *
 *  Created on: 03.10.2014
 *      Author: Daniel Keusch
 */


#include "LED_FRDM.h"
#include "LED.h"
#include "WAIT1.h"


/*!
 * \brief Test Routine for our LED Driver
 */
void testcolour(void){

	LedWHITE_On();
	WAIT1_Waitms(250);
	LedWHITE_Off();
	LedYELLOW_On();
	WAIT1_Waitms(250);
	LedYELLOW_Off();
	LedRED_On();
	WAIT1_Waitms(250);
	LedRED_Off();

	LedVIOLET_On();
	WAIT1_Waitms(250);
	LedVIOLET_Off();

	LedTORQUOISE_On();
	WAIT1_Waitms(250);
	LedTORQUOISE_Off();

	LedBLUE_On();
	WAIT1_Waitms(250);
	LedBLUE_Off();

	LedGREEN_On();
	WAIT1_Waitms(250);
	LedGREEN_Off();

}
