#include "Fight.h"
#if PL_HAS_REMOTE
	bool fightOn;
#endif


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




void FIGHT_Init(void) {
	fightOn = FALSE;
	FRTOS1_vTaskSuspend(fightTask);

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
		//DRV_Turn(360, 0);
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
	uint16_t test = 0;

	if(fightOn){
	switch(fight_state){
		case FIND_ENEMY:
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 30);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -30);
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
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 85);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 85);
			//fight_state = SEARCH_ENEMY;
			break;
		case WHITE_LINE_DETECTION:

			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -80);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -80);
			vTaskDelay(500/TRG_TICKS_MS);


			FRTOS1_vTaskResume(checkRefl);
			vTaskDelay(100/TRG_TICKS_MS);
			fight_state = FIND_ENEMY;


			break;
		case IDLE:
			//do nothing
			break;
		default:

			break;
	}

}
}
#endif


