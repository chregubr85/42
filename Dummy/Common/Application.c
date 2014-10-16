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
#include "CLS1.h"

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
		CLS1_SendStr("Button Red pressed\r", CLS1_GetStdio()->stdOut);
		break;
	case  EVNT_BTN_BLUE:
		LedBLUE_Neg();
		CLS1_SendStr("Button Blue pressed\r", CLS1_GetStdio()->stdOut);
		break;
	case  EVNT_BTN_YELLOW:
		LedBLUE_Neg();
		CLS1_SendStr("Button Yellow pressed\r", CLS1_GetStdio()->stdOut);
		break;
	case  EVNT_BTN_GREEN:
		LedBLUE_Neg();
		CLS1_SendStr("Button Green pressed\r", CLS1_GetStdio()->stdOut);
		break;
	case  EVNT_BTN_E:
		LedBLUE_Neg();
		CLS1_SendStr("Button E pressed\r", CLS1_GetStdio()->stdOut);
		break;
	case  EVNT_BTN_F:
		LedBLUE_Neg();
		CLS1_SendStr("Button F pressed\r", CLS1_GetStdio()->stdOut);
		break;
	case  EVNT_BTN_KEY:
		LedBLUE_Neg();
		CLS1_SendStr("Button Key pressed\r", CLS1_GetStdio()->stdOut);
		break;
	default:
		break;


	}

}
