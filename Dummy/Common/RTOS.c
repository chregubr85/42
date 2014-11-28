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




static portTASK_FUNCTION(T1, pvParameters) {
#if PL_HAS_ACCEL
	ACCEL_LowLevelInit();
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
#if PL_HAS_LINE_SENSOR
		REF_Danger();
#endif
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
  if (FRTOS1_xTaskCreate(CheckReflactance, (signed portCHAR *)"CheckReflactance", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, checkRefl) != pdPASS) {
       for(;;){} /* error */
     }
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
