/*!
** @file Application.c
** @version 1.0
** @brief
**         ToDo write brief
** @author S.Portmann
** @date 09.10.2014
*/


#include "Application.h"
#include "platform.h"
#include "LED.h"
#include "Keys.h"
#if PL_HAS_SHELL
#include "CLS1.h"
#endif
#if PL_HAS_BUZZER
#include "Buzzer.h"
#endif
#include "WAIT1.h"

void APP_start(void){

	PL_Init();
	EVNT_SetEvent(EVNT_INIT) ;
	APP_loop();
}

void APP_loop(void){

	for ( ; ; ) {
		KEY_Scan();
		EVNT_HandleEvent(APP_HandleEvent ) ;
	}
}

void APP_HandleEvent(EVNT_Handle event){
	uint8 duration = 100;
	uint8 freq = 100;

	switch(event){
	case EVNT_INIT:
		#if PL_IS_FRDM
			LedGREEN_On();
		#endif
		BUZ_Beep(40,2000);
	//	WAIT1_Waitms(1000);
		break;
	case EVNT_LED_HEARTBEAT:
		#if PL_IS_FRDM
			LedGREEN_Neg();
		#endif
			LED1_Neg();
		break;
	case  EVNT_BTN:

			BUZ_Beep(freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(2*freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(4*freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(2*freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(freq,duration);
			break;
#if PL_HAS_JOYSTICK
	case  EVNT_BTN_RED:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Red pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_BLUE:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Blue pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_YELLOW:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Yellow pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_GREEN:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Green pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_E:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button E pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_F:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button F pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_KEY:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Key pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
#endif
	default:
		break;


	}

}
