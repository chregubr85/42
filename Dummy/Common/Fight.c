#include "Fight.h"
#if PL_IS_ROBO

/*typedef enum Fightstat {
  DRIVE_DIRECT = 0,
  DRIVE_RIGHT,
  DRIVE_LEFT,
  TURN_RIGHT,
  TURN_LEFT,
  WHITE_LINE_DETECTION,
  SEARCH_ENEMY,
  FIND_ENEMY,
  IDLE
} Fightstate;*/

Fightstate fight_state = SEARCH_ENEMY;
static uint16_t cm, us;
bool fightOn;

static MOT_SpeedPercent speed=20;
static uint32_t i;


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
  DRV_EnableDisable(FALSE);
  DRV_EnableDisablePos(FALSE);
  fight_state = FIND_ENEMY;
  for(;;) {

	  FightmodusV2();
	  FRTOS1_vTaskDelay(10/TRG_TICKS_MS);
  }
}


void FIGHT_Init(void) {


}



void Fightmodus(void){

	switch(fight_state){
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

	case SEARCH_ENEMY:


	  	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 20);
	  	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -20);
		DRV_Turn(360, 0);
		us = US_Measure_us();
		cm = US_usToCentimeters(us, 22);

		if((cm<50)&&(cm>3)){
			fight_state=FIND_ENEMY;
		}
		break;
	case FIND_ENEMY:

		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 80);
		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 80);

		DRV_SetPos(10000);
		us = US_Measure_us();
		cm = US_usToCentimeters(us, 22);
		if((cm>50)){
			fight_state=SEARCH_ENEMY;
		}
		break;
	}
}

void FightmodusV2(void){
	switch(fight_state){
		case FIND_ENEMY:
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 20);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -20);
			fight_state = SEARCH_ENEMY;
			break;
		case SEARCH_ENEMY:
			us = US_Measure_us();
			cm = US_usToCentimeters(us, 22);

			if((cm<50)&&(cm>3)){
				fight_state=DRIVE_DIRECT;
			}else{
				fight_state = FIND_ENEMY;
			}
			break;
		case DRIVE_DIRECT:
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 80);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 80);
			fight_state = SEARCH_ENEMY;
			break;
		case WHITE_LINE_DETECTION:
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -80);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -80);
			for(i=0;i<1000000;i++);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
			FRTOS1_vTaskResume(checkRefl);
			fight_state = FIND_ENEMY;
			//DRV_EnableDisablePos(TRUE);
			//DRV_SetPos(-1000);

			break;
		case IDLE:
			//do nothing
			break;
		default:

			break;
	}

}
#endif


