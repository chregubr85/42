#include "Fight.h"

typedef enum Fightstat {
  DRIVE_DIRECT = 0,
  DRIVE_RIGHT,
  DRIVE_LEFT,
  TURN_RIGHT,
  TURN_LEFT,
  WHITE_LINE_DETECTION,
  SEARCH_ENEMIE,
  FIND_ENEMIE
} Fightstate;

static volatile Fightstate figth_state = SEARCH_ENEMIE; /* state machine state */
static uint16_t cm, us;

static MOT_SpeedPercent speed=20;


/*
typedef struct Fight_FSM{
	//Fightstate fightstate;
	MOT_MotorDevice mot_motordeviceright;
	MOT_MotorDevice mot_motordeviceleft;
}Fight_FSM;
static  Fight_FSM fight_fsm;
*/

static portTASK_FUNCTION(Fight_modus, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {

	  Fightmodus();
	  FRTOS1_vTaskDelay(10/TRG_TICKS_MS);
  }
}


void FIGHT_Init(void) {

  if(FRTOS1_xTaskCreate(Fight_modus,(signed portCHAR *) "Fight_m", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}



void Fightmodus(void){

	switch(figth_state){
	case DRIVE_DIRECT:
	  	  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), speed);
	  	  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), speed);
	  break;
	case DRIVE_RIGHT:

	  break;
	case DRIVE_LEFT:

	  break;
	case TURN_RIGHT:

	  break;
	case TURN_LEFT:

	  break;
	case WHITE_LINE_DETECTION:

		break;

	case SEARCH_ENEMIE:


	  	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 20);
	  	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -20);
		DRV_Turn(360, 0);
		us = US_Measure_us();
		cm = US_usToCentimeters(us, 22);

		if((cm<50)&&(cm>3)){
			figth_state=FIND_ENEMIE;
		}
		break;
	case FIND_ENEMIE:

		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 80);
		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 80);

		DRV_SetPos(10000);
		us = US_Measure_us();
		cm = US_usToCentimeters(us, 22);
		if((cm>50)){
			figth_state=SEARCH_ENEMIE;
		}
		break;
	}
}



