/**
 * \file
 * \brief LED driver
 * \author Christian Brunner
 *
 *
 * LED Driver Interface
 */

#include "platform.h"
#include "LED.h"
#include "WAIT1.h"

/*!
 * \brief Initial all LEDs (Off)
 */

void initLED(void){

	/* All LEDs off */
#if PL_NOF_LEDS >= 1
	LED1_Off();
#endif

#if PL_NOF_LEDS >= 2
	LED2_Off();
#endif

#if PL_NOF_LEDS >= 3
	LED3_Off();
#endif
}

/*!
 * \brief Test Routine for our LED Driver
 */

void testAllLed (void){
#if PL_NOF_LEDS >= 1
	LED1_On();
	WAIT1_Waitms(100);
	LED1_Off();
#endif

#if PL_NOF_LEDS >= 2
	LED2_On();
	WAIT1_Waitms(100);
	LED2_Off();
	WAIT1_Waitms(100);
	LED1_On();
	WAIT1_Waitms(100);
	LED2_On();
	WAIT1_Waitms(100);
	LED2_Off();
	LED1_Off();
#endif

#if PL_NOF_LEDS >= 3
	LED3_On();
	WAIT1_Waitms(100);
	LED3_Off();
	WAIT1_Waitms(100);
	LED2_On();
	WAIT1_Waitms(100);
	LED1_On();
	WAIT1_Waitms(100);
	LED3_Off();
	LED2_Off();
	LED1_Off();
#endif

}
