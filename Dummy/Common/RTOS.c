/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "platform.h"
#if PL_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"
#include "Event.h"
#include "Application.h"
#include "Trigger.h"
#include "Shell.h"
#include "Sem.h"
#if PL_HAS_ACCEL
	#include "Accel.h"
#endif
#if PL_HAS_REMOTE
	#include "RNet_App.h"
	#include "RApp.h"
	#include "remote.h"
#endif

TaskHandle_t checkRefl;
TaskHandle_t remoteTask;
TaskHandle_t fightTask;


static portTASK_FUNCTION(T1, pvParameters) {
#if PL_HAS_ACCEL
	ACCEL_LowLevelInit();
#endif
#if PL_HAS_REMOTE
	remoteInit();
#endif
#if PL_HAS_ANALOG_JOY
	AD1_Calibrate(TRUE);
	CalibXY();
#endif
#if PL_HAS_FIGHT
	FIGHT_Init();
#endif
  for(;;) {
	EVNT_SetEvent(EVNT_LED_HEARTBEAT);
    FRTOS1_vTaskDelay(1000/TRG_TICKS_MS);
  }
}

static portTASK_FUNCTION(App_loop, pvParameters) {
  for(;;) {
		KEY_Scan();
		EVNT_HandleEvent(APP_HandleEvent ) ;
		FRTOS1_vTaskDelay(10/TRG_TICKS_MS);

  }
}

static portTASK_FUNCTION(CheckReflactance, pvParameters) {
  for(;;) {
#if PL_HAS_LINE_SENSOR
		REF_Danger();
#endif
		FRTOS1_vTaskDelay(5/TRG_TICKS_MS);

  }
}

static portTASK_FUNCTION(Remote, pvParameters) {
	int32_t valMotR = 0;
	int32_t valMotL = 0;
	int32_t testi,testii,testi_old,testii_old;

	uint8_t buf[32];
	CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();

  for(;;) {

#if PL_HAS_REMOTE && PL_HAS_ANALOG_JOY
	uint8_t x,y;
	protocol42 txdata;


	GetXY(&x,&y);

	txdata.target = isROBOcop;
	txdata.type = anal_x;
	txdata.data = x;
	sendData42(txdata);

	txdata.type = anal_y;
	txdata.data = y;
	sendData42(txdata);
#endif
#if PL_HAS_MOTOR
	if(valX > 0) {
		valMotR = valY-valX;
		valMotL = valY;
	}
	else if (valX < 0) {
		valMotR = valY;
		valMotL = valY+valX;
	}
	else {
		valMotR = valY;
		valMotL = valY;
	}

	if((valY < 3) && (valY > -3)) {
		valMotR = 0;
		valMotL = 0;
	}


	testi = valMotR;
	testii = valMotL;

	if((testi != testi_old) || (testii != testii_old)) {

		CLS1_SendStr((unsigned char*)"Motor R Value: ", io->stdOut);
		CLS1_SendNum16s(testi, io->stdOut);

		CLS1_SendStr((unsigned char*)"     Motor L Value: ", io->stdOut);
		CLS1_SendNum32s(testii, io->stdOut);

		buf[0] = '\0';
		UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
		CLS1_SendStr(buf, io->stdOut);
		testi_old = testi;
		testii_old = testii;
	}



	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), valMotR);
	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT) , valMotL);


#endif

	FRTOS1_vTaskDelay(20/TRG_TICKS_MS);
  }
}

static portTASK_FUNCTION(Fight_modus, pvParameters) {

  DRV_EnableDisable(FALSE);
  DRV_EnableDisablePos(FALSE);
  fight_state = FIND_ENEMY;
  for(;;) {

	  FightmodusV2();
	  FRTOS1_vTaskDelay(10/TRG_TICKS_MS);
  }
}

#if PL_HAS_ACCEL
static portTASK_FUNCTION(AccelObserv, pvParameters) {
	int16_t x,y,z;
	for(;;) {
		ACCEL_GetValues(&x, &y, &z);
		if(z < 800 ){
			EVNT_SetEvent(EVNT_FREEFALL);
		}
		FRTOS1_vTaskDelay(10/TRG_TICKS_MS);
	}
}
#endif

void RTOS_Run(void) {
  FRTOS1_vTaskStartScheduler();
}

void RTOS_Init(void) {

  if (FRTOS1_xTaskCreate(T1, (signed portCHAR *)"T1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (FRTOS1_xTaskCreate(App_loop, (signed portCHAR *)"App_loop", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
      for(;;){} /* error */
    }
#if PL_HAS_LINE_SENSOR
  if (FRTOS1_xTaskCreate(CheckReflactance, (signed portCHAR *)"CheckReflactance", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &checkRefl) != pdPASS) {
       for(;;){} /* error */
     }
#endif

#if PL_HAS_REMOTE
  if (FRTOS1_xTaskCreate(Remote, (signed portCHAR *)"Remote", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &remoteTask) != pdPASS) {
       for(;;){} /* error */
     }
#endif

#if PL_HAS_FIGHT
  if(FRTOS1_xTaskCreate(Fight_modus,(signed portCHAR *) "Fight_m", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &fightTask) != pdPASS) {
      for(;;){} /* error */
    }
#endif

#if PL_HAS_ACCEL
  if(FRTOS1_xTaskCreate(AccelObserv,(signed portCHAR *) "AccelObserv", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &fightTask) != pdPASS) {
      for(;;){} /* error */
    }
#endif
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
