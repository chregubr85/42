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


