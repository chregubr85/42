/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
  */

#include "platform.h"
#if PL_HAS_TIMER
#include "Timer.h"
#include "Event.h"

void TMR_OnInterrupt(void) {
  time++;
  if (time==100){
	  EVNT_SetEvent(EVNT_LED_HEARTBEAT);
	  time = 0;
  }
}

void TMR_Init(void) {
  time = 0;
}

void TMR_Deinit(void) {
  /* nothing needed right now */
}

#endif /*PL_HAS_TIMER*/
