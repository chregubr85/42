#ifndef __FIGHT_H_
#define __FIGHT_H_


#include "platform.h"
#include "Application.h"
#include "Motor.h"
#include "Drive.h"

#define FightOn		vTaskResume("Fight")
#define FightOff	vTaskSuspend("Fight")

typedef enum{
  DRIVE_DIRECT = 0,
  DRIVE_RIGHT,
  DRIVE_LEFT,
  TURN_RIGHT,
  TURN_LEFT,
  WHITE_LINE_DETECTION,
  SEARCH_ENEMY,
  FIND_ENEMY,
  IDLE
} Fightstate;

extern Fightstate fight_state;
extern bool fightOn;



extern void FIGHT_Init(void);
extern void Fightmodus(void);
extern void FightmodusV2(void);

#endif /*__FIGHT_H_*/
