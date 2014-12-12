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


	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), valMotR);
	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT) , valMotL);


#endif

	FRTOS1_vTaskDelay(20/TRG_TICKS_MS);
  }
}

static portTASK_FUNCTION(Fight_modus, pvParameters) {
#if PL_HAS_DRIVE
	  DRV_EnableDisable(FALSE);
	  DRV_EnableDisablePos(FALSE);
#endif
  fight_state = FIND_ENEMY;
  FRTOS1_vTaskDelay(100/TRG_TICKS_MS);
  for(;;) {
	  FRTOS1_vTaskDelay(10/TRG_TICKS_MS);
	  FightmodusV2();
  }
}

#if PL_HAS_ACCEL && PL_IS_ROBO
static portTASK_FUNCTION(AccelObserv, pvParameters) {

	for(;;) {
		static int16_t x,y,z;

		ACCEL_GetValues(&x, &y, &z);

		if(z < -200){
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
  if(FRTOS1_xTaskCreate(AccelObserv,(signed portCHAR *) "AccelObserv", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
      for(;;){} /* error */
    }
#endif
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
