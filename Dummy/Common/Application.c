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
#include "Keys.h"

void run_app(void){
	EVNT_SetEvent(EVNT_INIT) ;
	for ( ; ; ) {
		KEY_Scan();
		EVNT_HandleEvent(APP_HandleEvent ) ;

	}
}


void APP_HandleEvent(EVNT_Handle event){
	switch(event){
	case EVNT_INIT:
		LedGREEN_On();
		break;
	case EVNT_LED_HEARTBEAT:
		LedGREEN_Neg();
		break;
	case  EVNT_BTN_RED:
		LedBLUE_Neg();
		break;
	case  EVNT_BTN_BLUE:
		LedBLUE_Neg();
		break;
	case  EVNT_BTN_YELLOW:
		LedBLUE_Neg();
		break;
	case  EVNT_BTN_GREEN:
		LedBLUE_Neg();
		break;
	case  EVNT_BTN_E:
		LedBLUE_Neg();
		break;
	case  EVNT_BTN_F:
		LedBLUE_Neg();
		break;
	case  EVNT_BTN_KEY:
		LedBLUE_Neg();
		break;
	default:
		break;


	}

}
