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
#if PL_HAS_EVENTS
#include "Event.h"
#endif
#if PL_HAS_TRIGGER
#include "Trigger.h"
#endif

uint16 time;

void TMR_OnInterrupt(void) {

#if !PL_HAS_RTOS
 time++;
 if ((time*TMR_TICK_MS)>=1000){

#if PL_HAS_EVENTS
	  EVNT_SetEvent(EVNT_LED_HEARTBEAT);
#endif
	  time = 0;
 }
#if PL_HAS_TRIGGER
  TRG_IncTick();
#endif
#endif
}

void TMR_Init(void) {
  time = 0;
}

void TMR_Deinit(void) {
  /* nothing needed right now */
}

#endif /*PL_HAS_TIMER*/
