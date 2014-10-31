/*!
** @file Application.c
** @version 1.0
** @brief
**         ToDo write brief an mutti
** @author S.Portmann
** @date 09.10.2014
*/


#include "Application.h"


void APP_start(void){
	PL_Init();
	EVNT_SetEvent(EVNT_INIT) ;
	SHELL_Init();
	RTOS_Init();
	RTOS_Run();
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
		#elif PL_IS_ROBO
			BUZ_Beep(40,2000);
		#endif
		break;
	case EVNT_LED_HEARTBEAT:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#elif PL_IS_ROBO
			LED1_Neg();
		#endif
		break;
		#if PL_IS_ROBO
	case  EVNT_BTN:
		MEALY_Step();
		for(int i =0; i < 4; i++){
			BUZ_Beep(freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(2*freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(4*freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(2*freq,duration);
			WAIT1_Waitms(duration);
			BUZ_Beep(freq,duration);
			WAIT1_Waitms(duration);
		}
			break;
		#endif
#if PL_HAS_JOYSTICK
	case  EVNT_BTN_RED_PRESSED:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Red pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_BLUE_PRESSED:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Blue pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_YELLOW_PRESSED:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Yellow pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_GREEN_PRESSED:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Green pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_E_PRESSED:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button E pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_F_PRESSED:
		#if PL_IS_FRDM
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button F pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_KEY_PRESSED:
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
