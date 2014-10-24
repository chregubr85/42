/*!
** @file Application.h
** @version 1.0
** @brief
**         ToDO: write brief
** @author S.Portmann
** @date 03.10.2014
*/

#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "platform.h"

#if PL_HAS_EVENTS
#include "Event.h"
#endif

#include "platform.h"
#if PL_NOF_LEDS >=1
#include "LED.h"
#endif

#if PL_HAS_KEYS
#include "Keys.h"
#endif

#if PL_HAS_SHELL
#include "CLS1.h"
#endif

#if PL_HAS_BUZZER
#include "Buzzer.h"
#endif

#if PL_HAS_MEALY
#include "Mealy.h"
#endif

#if PL_HAS_RTOS
#include "RTOS.h"
#endif

#include "WAIT1.h"


void APP_start(void);

void APP_loop(void);

void APP_HandleEvent(EVNT_Handle event);

#endif /*__APPLICATION_H_*/
