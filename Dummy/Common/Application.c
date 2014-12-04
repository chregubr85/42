/*!
** @file Application.c
** @version 1.0
** @brief
**
** @author S.Portmann
** @date 09.10.2014
*/


#include "Application.h"


void APP_start(void){
	PL_Init();
	EVNT_SetEvent(EVNT_INIT) ;
#if PL_HAS_SHELL
	SHELL_Init();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Init();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Init();
#endif
#if PL_HAS_MOTOR
	MOT_Init();
#endif
#if PL_HAS_MOTOR_TACHO
	TACHO_Init();
#endif
#if PL_HAS_PID
	PID_Init();
#endif
#if PL_HAS_DRIVE
	DRV_Init();
#endif
#if PL_HAS_ULTRASONIC
	US_Init();
#endif
#if PL_HAS_ACCEL
	ACCEL_Init();
#endif

#if PL_HAS_RTOS
	RTOS_Init();
	#if PL_HAS_SEMAPHORE
		SEM_Init();
	#endif
	RTOS_Run();
#else
	APP_loop();
#endif
}

void APP_loop(void){

	for ( ; ; ) {
		KEY_Scan();
		EVNT_HandleEvent(APP_HandleEvent ) ;
	}
}

void APP_DebugPrint(unsigned char *str) {
#if PL_HAS_SHELL
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
#endif
}

void APP_HandleEvent(EVNT_Handle event){
	uint8 duration = 100;
	uint8 freq = 100;
	int32_t aleft = 0;
	int32_t brigth = 0;

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
			LedGREEN_Neg();
		#elif PL_IS_ROBO
			LED2_Neg();
		#endif
		break;
		#if PL_IS_ROBO
	case  EVNT_BTN:
	//	MEALY_Step();
		for(int i =0; i < 4; i++){
			BUZ_Beep(freq,duration);
			FRTOS1_vTaskDelay(duration/TRG_TICKS_MS);
			//WAIT1_Waitms(duration);
			BUZ_Beep(2*freq,duration);
			FRTOS1_vTaskDelay(duration/TRG_TICKS_MS);
			//WAIT1_Waitms(duration);
			BUZ_Beep(4*freq,duration);
			FRTOS1_vTaskDelay(duration/TRG_TICKS_MS);
			//WAIT1_Waitms(duration);
			BUZ_Beep(2*freq,duration);
			FRTOS1_vTaskDelay(duration/TRG_TICKS_MS);
			//WAIT1_Waitms(duration);
			BUZ_Beep(freq,duration);
			FRTOS1_vTaskDelay(duration/TRG_TICKS_MS);
			//WAIT1_Waitms(duration);
		}
			break;
	case EVNT_BTN_LPRESSED:
		#if PL_HAS_LINE_SENSOR
			EVNT_SetEvent(EVNT_REF_START_STOP_CALIBRATION) ;
		#endif
	#endif
			break;
#if PL_HAS_MOTOR
	case EVNT_DONT_FALL_DOWN:
		aleft = *DRV_GetSpeedLeft();
		brigth = *DRV_GetSpeedRight();
		DRV_SetSpeed(-aleft,-brigth);
		break;
#endif

#if PL_HAS_JOYSTICK
	case  EVNT_BTN_RED_PRESSED:
		#if PL_IS_FRDM & !PL_HAS_RADIO
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Red pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_BLUE_PRESSED:
		#if PL_IS_FRDM & !PL_HAS_RADIO
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Blue pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_YELLOW_PRESSED:
		#if PL_IS_FRDM & !PL_HAS_RADIO
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Yellow pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_GREEN_PRESSED:
		#if PL_IS_FRDM & !PL_HAS_RADIO
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button Green pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_E_PRESSED:
		#if PL_IS_FRDM & !PL_HAS_RADIO
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button E pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_F_PRESSED:
		#if PL_IS_FRDM & !PL_HAS_RADIO
			LedBLUE_Neg();
		#endif
		#if PL_HAS_SHELL
			CLS1_SendStr("Button F pressed\r", CLS1_GetStdio()->stdOut);
		#endif
		break;
	case  EVNT_BTN_KEY_PRESSED:
		#if PL_IS_FRDM & !PL_HAS_RADIO
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
