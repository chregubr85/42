/*!
** @file Application.c
** @version 1.0
** @brief
**         ToDo write brief
** @author S.Portmann
** @date 09.10.2014
*/

#include "Application.h"
#include "LED.h"

void run_app(void){
	EVNT_SetEvent(EVNT_INIT) ;
	for ( ; ; ) {
		EVNT_HandleEvent(APP_HandleEvent ) ;
	}
}


void APP_HandleEvent(EVNT_Handle event){
	switch(event){
	case EVNT_INIT:
		LedGREEN_On();
		break;
	case EVNT_LED_HEARTBEAT:
		LedRED_Neg();

	default:
		break;


	}

}
