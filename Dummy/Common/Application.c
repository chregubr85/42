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

void APP_start(void){
	EVNT_SetEvent(EVNT_INIT) ;
	PL_Init();

	for ( ; ; ) {
		BUZ_Beep(1000,1000);
		KEY_Scan();
		EVNT_HandleEvent(APP_HandleEvent ) ;

	}
}


void APP_HandleEvent(EVNT_Handle event){
	switch(event){
	case EVNT_INIT:
		#if PL_IS_FRDM
			LedGREEN_On();
		#endif
		break;
	case EVNT_LED_HEARTBEAT:
		#if PL_IS_FRDM
			LedGREEN_Neg();
		#endif
		break;
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
	default:
		break;


	}

}
