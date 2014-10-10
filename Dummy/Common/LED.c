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
#if (PL_NOF_LEDS >= 1) != PL_HAS_KEYS
	LED1_Off();
#endif

#if PL_NOF_LEDS >= 2
	LED2_Off();
#endif

#if PL_NOF_LEDS >= 3
	LED3_Off();
#endif
}


#if 0
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

/*!
 * \brief Test Routine for our LED Driver
 */

void led12On(void){

	LED1_On();
	LED2_On();
}

/*!
 * \brief mix colour on for RGB Led
 */

void led13On(void){

	LED1_On();
	LED3_On();
}

/*!
 * \brief mix colour on for RGB Led
 */

void led23On(void){

	LED2_On();
	LED3_On();
}

/*!
 * \brief mix colour on for RGB Led
 */

void led123On(void){

	LED1_On();
	LED2_On();
	LED3_On();
}

/*!
 * \brief mix colour off for RGB Led
 */
void led12Off(void){

	LED1_Off();
	LED2_Off();
}

/*!
 * \brief mix colour off for RGB Led
 */

void led13Off(void){

	LED1_Off();
	LED3_Off();
}

/*!
 * \brief mix colour off for RGB Led
 */

void led23Off(void){

	LED2_Off();
	LED3_Off();
}

/*!
 * \brief mix colour off for RGB Led
 */

void led123Off(void){

	LED1_Off();
	LED2_Off();
	LED3_Off();
}

#endif

